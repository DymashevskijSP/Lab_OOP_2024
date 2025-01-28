#include "game_state.h"
#include "cell_info.h"
#include "abilities/double_attack.h"
#include "abilities/scanner.h"
#include "abilities/random_attack.h"
#include "bad_file.h"
namespace sea_battle {

GameState::GameState(const Board& enemy_board_, 
                       const Board& enemy_board_view_, 
                       const Board& ally_board_, 
                       const std::vector<std::shared_ptr<Ship>>& enemy_ships_, 
                       const std::vector<std::shared_ptr<Ship>>& ally_ships_,
                       std::vector<std::unique_ptr<Ability>> abilities
                       ): enemy_board(enemy_board_)
                        , enemy_board_view(enemy_board_view_)
                        , ally_board(ally_board_)
                        , enemy_ships(enemy_ships_)
                        , ally_ships(ally_ships_)
                        , abilities(std::move(abilities)){}

void GameState::write_abilities(std::ostream& stream) {
  size_t ability_size = abilities.size();
  stream.write(reinterpret_cast<const char*>(&ability_size), sizeof(ability_size));
  for(const auto& ability: abilities) {
    size_t ability_type;
    if(reinterpret_cast<DoubleAttackAbility*>(ability.get())) {
      ability_type = 0;
    } else if(reinterpret_cast<RandomAttackAbility*>(ability.get())) {
      ability_type = 1;
    } else if(reinterpret_cast<ScannerAbility*>(ability.get())) {
      ability_type = 2;
    }
    stream.write(reinterpret_cast<const char*>(&ability_type), sizeof(ability_type));
  }
}

void GameState::write_ships(std::ostream& stream, std::vector<std::shared_ptr<Ship>> ships){
  size_t sz = ships.size();
  stream.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
  check_stream(stream);
  for(const auto& ship: ships) {
    size_t ssize = ship->size();
    stream.write(reinterpret_cast<const char*>(&ssize), sizeof(ssize));
    check_stream(stream);
    for(const auto& segment: ship->get()) {
      stream.write(reinterpret_cast<const char*>(&segment), sizeof(segment));
      check_stream(stream);
    }
  }
}

void GameState::write_board(std::ostream& stream, const std::vector<std::vector<Board::board_cell_type>>& board, const std::vector<std::shared_ptr<Ship>>& ships) {
  size_t width = board.size();
  size_t height = board[0].size();
  stream.write(reinterpret_cast<const char*>(&width), sizeof(width));
  check_stream(stream);
  stream.write(reinterpret_cast<const char*>(&height), sizeof(height));
  check_stream(stream);
  std::unordered_map<Ship*, int> ship2num;
  
  for(size_t i = 0; i < ships.size(); i++) {
     ship2num[ships[i].get()] = i;
  }

  for(const auto& line: board) {
    for(const auto& cell: line) {
      if(std::holds_alternative<Cell>(cell)) {
        CellInfo cell_info(std::get<Cell>(cell));
        stream << cell_info;
      } else {
        auto [ship, num] = std::get<Board::board_ship_type>(cell);
        CellInfo cell_info(Cell::SHIP, ship2num[ship.get()], num);
        stream << cell_info;
        check_stream(stream);
      }
    }
  }
 
}

std::ostream& operator << (std::ostream& stream, GameState& state) {
  state.write_abilities(stream);
  state.write_ships(stream, state.enemy_ships);
  state.write_ships(stream, state.ally_ships);
  state.write_board(stream, state.enemy_board.get_content(), state.enemy_ships);
  state.write_board(stream, state.enemy_board_view.get_content(), state.enemy_ships);
  state.write_board(stream, state.ally_board.get_content(), state.ally_ships);
  
  return stream;
}

std::vector<Ability*> GameState::read_abilities(std::istream& stream) {
  std::vector<Ability*> result;
  size_t abilities_size;
  stream.read((char*)&abilities_size, sizeof(abilities_size));
  check_stream(stream);
  for(size_t i = 0; i < abilities_size; i++) {
    size_t atype;
    stream.read((char*)&atype, sizeof(atype));
    check_stream(stream);
    if (atype == 0) {
      result.push_back(new DoubleAttackAbility());
    } else if (atype == 1) {
      result.push_back(new RandomAttackAbility());
    } else if (atype == 2) {
      result.push_back(new ScannerAbility());
    }
  }
  return result;

}

GameState GameState::read_state(std::istream& stream) {
  std::vector<Ability*> abilities = GameState::read_abilities(stream);
  std::vector<Ship> enemy_ships = GameState::read_ships(stream);
  std::vector<Ship> ally_ships = GameState::read_ships(stream);
  std::vector<std::shared_ptr<Ship>> enemy_ships_;
  std::vector<std::shared_ptr<Ship>> ally_ships_;
  std::vector<std::unique_ptr<Ability>> abilities_;
  for(const auto& ship: enemy_ships) {
    enemy_ships_.push_back(std::make_shared<Ship>(ship));
  } 
  for(const auto& ship: ally_ships) {
    ally_ships_.push_back(std::make_shared<Ship>(ship));
  }
  for(const auto& ability: abilities) {
    abilities_.emplace_back(ability);
  }
  Board enemy_board(GameState::read_board(stream, enemy_ships_));
  Board enemy_board_view(GameState::read_board(stream, enemy_ships_));
  Board ally_board(GameState::read_board(stream, ally_ships_));
  
  return GameState(enemy_board, enemy_board_view, ally_board, enemy_ships_, ally_ships_, std::move(abilities_));
}

std::vector<Ship> GameState::read_ships(std::istream& stream) {
  std::vector<Ship> result;
  size_t ships_size;
  stream.read((char*)&ships_size, sizeof(ships_size));
  check_stream(stream);
  for(size_t i = 0; i < ships_size; i++) {
    size_t ssize;
    stream.read((char*)&ssize, sizeof(ssize));
    std::vector<Segment> segments;
    for(size_t j = 0; j < ssize; j++) {
      Segment seg;
      stream.read((char*)&seg, sizeof(seg));
      check_stream(stream);
      segments.push_back(seg);
    }
    result.emplace_back(segments);
  }
  return result;
}

std::vector<std::vector<Board::board_cell_type>> GameState::read_board(std::istream& stream, const std::vector<std::shared_ptr<Ship>>& ships) {
  size_t width;
  size_t height;
  stream.read((char*)&width, sizeof(width));
  check_stream(stream);
  stream.read((char*)&height, sizeof(height));
  check_stream(stream);
  std::vector<std::vector<Board::board_cell_type>> result(width, std::vector<Board::board_cell_type>(height, Cell::EMPTY));
  for(size_t i = 0; i < width; i++) {
    for(size_t j = 0; j < height; j++) {
      CellInfo info(Cell::EMPTY);
      stream.read((char*)&info, sizeof(info));
      check_stream(stream);
      if (info.get_ship_num() == -1) {
        result[i][j] = info.get_cell_type();
      } else {
        result[i][j] = std::make_pair(ships[info.get_ship_num()],info.get_segment_num());
      }
    }
  }
  return result;
}

Board GameState::get_enemy_board() {
  return enemy_board;
}

Board GameState::get_enemy_board_view() {
  return enemy_board_view;
}

std::vector<std::shared_ptr<Ship>> GameState::get_enemy_ships() {
  return enemy_ships;
}

Board GameState::get_ally_board() {
  return ally_board;
}

std::vector<std::shared_ptr<Ship>> GameState::get_ally_ships() {
  return ally_ships;
}

std::vector<std::unique_ptr<Ability>>& GameState::get_abilities(){
  return abilities;
}

void GameState::check_stream(const std::basic_ios<char>& stream) {
  if(!stream) {
    throw exceptions::BadFileException();
  }
}

} // namespace sea_battle
