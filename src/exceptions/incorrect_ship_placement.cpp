#include "incorrect_ship_placement.h"
#include <string>

namespace exceptions {

const char* IncorrectShipPlacementException::what() const noexcept {
  return "location of ship is incorrect";
}

} // namespace exceptions
