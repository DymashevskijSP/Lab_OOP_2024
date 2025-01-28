#include "move.h"
namespace sea_battle {
Move::Move(MoveType type_, BoardCoordinates coordinates_)
    : type(type_), coordinates(coordinates_) {}

MoveType Move::get_move_type() { return type; }

BoardCoordinates Move::get_coordinates() { return coordinates; }
} // namespace sea_battle
