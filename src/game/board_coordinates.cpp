#include "board_coordinates.h"

namespace sea_battle {

BoardCoordinates::BoardCoordinates(size_t x, size_t y): x_(x), y_(y){
}

size_t BoardCoordinates::x() const & {
  return x_;
}

size_t BoardCoordinates::y() const & {
  return y_;
}
} //namespace sea_battle
