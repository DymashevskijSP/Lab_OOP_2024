#include "board.h"
#include "ship.h"
#include "ability.h"
#include <ostream>
#include <istream>
#include <memory>
namespace sea_battle {

class GameState{

public:
  GameState(const Board& enemy_board_,
            const Board& enemy_board_view_, 
            const Board& ally_board_, 
            const std::vector<std::shared_ptr<Ship>>& enemy_ships,
            const std::vector<std::shared_ptr<Ship>>& ally_ships,
            std::vector<std::unique_ptr<Ability>> abilities
            );
  friend std::ostream& operator<<(std::ostream& stream, GameState& state);
  static GameState read_state(std::istream& stream);
  Board get_enemy_board();
  Board get_ally_board();
  Board get_enemy_board_view();
  std::vector<std::shared_ptr<Ship>> get_enemy_ships();
  std::vector<std::shared_ptr<Ship>> get_ally_ships();
  std::vector<std::unique_ptr<Ability>>& get_abilities();
private:
  static std::vector<Ability*> read_abilities(std::istream& stream);
  static std::vector<Ship> read_ships(std::istream& stream);
  static std::vector<std::vector<Board::board_cell_type>> read_board(std::istream& stream, const std::vector<std::shared_ptr<Ship>>& ships);
  void write_abilities(std::ostream& stream);
  void write_ships(std::ostream& stream, std::vector<std::shared_ptr<Ship>> ships);
  void write_board(std::ostream& stream, const std::vector<std::vector<Board::board_cell_type>>& board, const std::vector<std::shared_ptr<Ship>>& ships);
  Board enemy_board;
  Board enemy_board_view;
  Board ally_board;
  std::vector<std::shared_ptr<Ship>> enemy_ships;
  std::vector<std::shared_ptr<Ship>> ally_ships;
  std::vector<std::unique_ptr<Ability>> abilities;
  static void check_stream(const std::basic_ios<char>& stream);
};
} //namespace sea_battle
