#include "base_exception.h"
#include "incorrect_ship_placement.h"
#include "game_controller.h"
#include "parameters.h"
#include "board.h"
#include "abilities/double_attack.h"
#include "abilities/scanner.h"
#include "abilities/random_attack.h"
#include "ability_error.h"
#include "bad_file.h"
#include "interface_info.h"

#include <ctime>
#include <iostream>
#include <fstream>

namespace sea_battle {

GameController::GameController(Parameters parameters, view::View* view_): 
  ally_board(parameters.width(), parameters.height(), true), 
  enemy_board(parameters.width(), parameters.height(), true), 
  enemy_board_view(parameters.width(), parameters.height(), false), 
  view(view_)  {
}

void GameController::make_attack(BoardCoordinates coordinates) {
  static_cast<void>(enemy_board_view.do_hit(coordinates)); // discarding return value for board view
  auto [ship, num] = enemy_board.do_hit(coordinates);
  attack_callback(enemy_board, coordinates);
  bool ship_was_not_destroyed = ship ? !ship->is_destroyed() : false;
  if (ship) {
    ship->do_hit(num);
    enemy_board_view.place_ship_segment_view(coordinates, ship->is_segment_destroyed(num));  
   }
   attack_callback = [](Board&, BoardCoordinates){};
   if (ship_was_not_destroyed && ship->is_destroyed()) {
      ability_manager.add_random_ability();
   }
}

void GameController::activate_ability(Board& board) {
  BoardCoordinates coordinates = ability_manager.is_next_targeted() ? view->get_coordinates() : BoardCoordinates(0, 0);
  std::string result = ability_manager.activate_next_ability(board, coordinates, attack_callback, enemy_ship_manager);
  view->draw_ability_result(result);
}

void GameController::init_enemy_ships() {
  // full random placement
  enemy_ship_manager = ShipManager();
  enemy_board = Board(enemy_board.get_width(), enemy_board.get_height(), true);
  enemy_board_view = Board(enemy_board.get_width(), enemy_board.get_height(), false);
  std::vector<size_t> ship_count = get_ships_count();
  std::srand(std::time(0));
  for(size_t i = 1; i < ship_count.size(); i++) {
    for(size_t j = 0; j < ship_count[i]; j++) {
      enemy_ship_manager.add_ship(i);
    }
  }
  auto ships = enemy_ship_manager.get_ships();
  for(const auto& ship: ships) {
    while (true) {
      size_t x = std::rand() % enemy_board.get_width();
      size_t y = std::rand() % enemy_board.get_height();
      bool is_vertical = std::rand() % 2;
      try {
        enemy_board.place_ship(ship, is_vertical ? Direction::VERTICAL : Direction::HORIZONTAL, {x, y});
      } catch (const exceptions::IncorrectShipPlacementException&) {
        continue;
      }
      break;
    }
  }
}

void GameController::start_game() {
  init_ally_ships();
  init_enemy_ships(); 
  init_abilities();  
  play_game();
}

std::vector<size_t> GameController::get_ships_count() {
  std::vector<size_t> res(5, 0);
  res[4] = std::min(enemy_board.get_width(), enemy_board.get_height()) / 8;
  res[3] = std::min(enemy_board.get_width(), enemy_board.get_height()) / 5;
  res[2] = std::min(enemy_board.get_width(), enemy_board.get_height()) / 4;
  res[1] = std::min(enemy_board.get_width(), enemy_board.get_height()) / 3;
  return res;
}

void GameController::init_ally_ships() {
  personal_ship_manager = ShipManager();
  ally_board = Board(ally_board.get_width(), ally_board.get_height(), false);
  std::vector<size_t> ship_count = get_ships_count();  
  for(size_t i = 1; i < ship_count.size(); i++) {
    for(size_t j = 0; j < ship_count[i]; j++) {
      personal_ship_manager.add_ship(i);
    }
  }

  auto ships = personal_ship_manager.get_ships();
  size_t cnt = 0;
  for(size_t i = 1; i < ship_count.size(); i++) {
    for(size_t j = 0; j < ship_count[i]; j++) {
      while (true) {
        try {
          auto [coordinates, direction] = view->get_ship(i);
          Direction d = direction ? Direction::VERTICAL : Direction::HORIZONTAL;
          ally_board.place_ship(ships[cnt], d, coordinates);
        } catch(exceptions::BaseException& e) {
          view->draw_exception(e);
          continue;
        }
        cnt++;
        break;
      }
    }
 }

}

void GameController::init_abilities() {
  ability_manager.clear();
  std::vector<std::unique_ptr<Ability>> start_abilities;
  start_abilities.push_back(std::move(std::make_unique<RandomAttackAbility>()));
  start_abilities.push_back(std::move(std::make_unique<DoubleAttackAbility>()));
  start_abilities.push_back(std::move(std::make_unique<ScannerAbility>()));
  std::random_shuffle(start_abilities.begin(), start_abilities.end()); 
  for(auto& ability_ptr: start_abilities) {
    ability_manager.add_ability(std::move(ability_ptr));
  }
  
}

void GameController::play_game() {
  size_t cnt = 0;
  while (enemy_ship_manager.has_undestroyed_ships()) {
    view->draw_boards(enemy_board_view.get_view(), ally_board.get_view());
    view::InterfaceInfo info(enemy_ship_manager.get_undestroyed_ships_counter(), ability_manager.get_abilities_counter(), ability_manager.get_next_ability_name());
    view->draw_interface(info);
    try {
      Move move = view->get_move();
      if (move.get_move_type() == MoveType::ATTACK) {
        BoardCoordinates coordinates = move.get_coordinates();
        make_attack({coordinates.x(), coordinates.y()});
      } else if (move.get_move_type() == MoveType::ABILITY) {
        activate_ability(enemy_board);
      } else if (move.get_move_type() == MoveType::QUIT) {
        break;
      } else if (move.get_move_type() == MoveType::SAVE) {
        save_game();
      } else if (move.get_move_type() == MoveType::LOAD) {
        load_game();
      }
    } catch(const exceptions::BaseException& e) {
      view->draw_exception(e);
      if(e.is_fatal) {
        break;
      }
      continue;
    }
    if(!enemy_ship_manager.has_undestroyed_ships()) break;

    auto [ship, num] = ally_board.do_hit(BoardCoordinates(cnt / ally_board.get_width(), cnt%ally_board.get_height()));
    if(ship) {
      ship->do_hit(num);
    }
    cnt++;
    if(cnt == ally_board.get_width()*ally_board.get_height()) {
      cnt = 0;
    }
    if(!personal_ship_manager.has_undestroyed_ships()) {
      break;
    }
  }
  if(!personal_ship_manager.has_undestroyed_ships()) {
    start_game();
  } else if (!enemy_ship_manager.has_undestroyed_ships()) {
    init_enemy_ships();
    play_game();
  }
}

void GameController::load_game() {
  std::fstream f;
  try {
    std::string filename;
    filename = "saves/" + view->get_save_name();
    f.open(filename);
    if(!f.is_open()){
      f.close();
      throw exceptions::BadFileException(); 
    }
    GameState state = GameState::read_state(f);

    enemy_ship_manager = ShipManager(state.get_enemy_ships());
    personal_ship_manager = ShipManager(state.get_ally_ships());
    enemy_board = state.get_enemy_board();
    enemy_board_view = state.get_enemy_board_view();
    ally_board = state.get_ally_board();
    ability_manager.clear();
  
    for(std::unique_ptr<Ability>& ability: state.get_abilities()) {
      ability_manager.add_ability(std::move(ability));
    }
    f.close();
  } catch (...) {
    f.close();
    std::rethrow_exception(std::current_exception());
  }
}

void GameController::save_game() {
  std::ofstream f;
  try {
    std::string filename = "saves/" + view->get_save_name();
    f.open(filename); 
    if(!f.is_open()){
      f.close();
      throw exceptions::BadFileException(); 
    }
    std::queue<std::unique_ptr<Ability>>& abilities = ability_manager.get_abilities();
    std::vector<std::unique_ptr<Ability>> abilities_vector;
    while (!abilities.empty()) {
      abilities_vector.push_back(std::move(abilities.front()));
      abilities.pop();
    }

    for(const auto& ability: abilities_vector) {
      std::unique_ptr<Ability> copy(ability->clone());
      ability_manager.add_ability(std::move(copy));
    }
    GameState state(enemy_board, enemy_board_view, ally_board, enemy_ship_manager.get_ships(), personal_ship_manager.get_ships(), std::move(abilities_vector));
    f<<state;
    f.flush();
    f.close();
  } catch(...) {
    f.close();
    std::rethrow_exception(std::current_exception());
  }
}

} //  namespace sea_battle
