#include "illegal_move.h"
#include <string>

namespace exceptions {

const char* IllegalMoveException::what() const noexcept {
  return "wrong move";
}

} // namespace exceptions
