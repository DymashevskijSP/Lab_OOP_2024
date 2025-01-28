#include "ability_error.h"
#include <string>

namespace exceptions {

const char* AbilityException::what() const noexcept {
  return "incorrect use of abilities";
}

} // namespace exceptions
