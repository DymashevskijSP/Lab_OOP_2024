#include "bad_file.h"
#include <string>

namespace exceptions {

const char* BadFileException::what() const noexcept {
  return "can't operate with this file";
}

} // namespace exceptions
