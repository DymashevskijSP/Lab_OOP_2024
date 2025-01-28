#include "board_coordinates.h"
namespace sea_battle {
enum class MoveType {ABILITY, ATTACK, QUIT, SAVE, LOAD};

class Move {
public:
 Move(MoveType type_, BoardCoordinates coordinates_);
 MoveType get_move_type();
 BoardCoordinates get_coordinates();
private:
  MoveType type;
  BoardCoordinates coordinates;
};
} // namespace sea_battle
