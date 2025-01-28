#include "board.h"
#include "parameters.h"
#include "view.h"
#include "ability_manager.h"
#include "game_state.h"
#include "ship_manager.h"
#include <functional>

namespace sea_battle {

class GameController {
  Board ally_board;
  Board enemy_board;
  Board enemy_board_view;
  std::unique_ptr<view::View> view;
  AbilityManager ability_manager;
  ShipManager enemy_ship_manager;
  ShipManager personal_ship_manager;
  void activate_ability(Board& board);
  void make_attack(BoardCoordinates coordinates);
  std::function<void(Board&, BoardCoordinates)> attack_callback = [](Board&, BoardCoordinates){};
  void init_enemy_ships();
  void play_game();
  void init_ally_ships();
  void load_game();
  std::vector<size_t> get_ships_count();
  void init_abilities();
  void save_game();
public:
  GameController(Parameters parameters, view::View *view_);
  void start_game();
};
} // namespace sea_battle
