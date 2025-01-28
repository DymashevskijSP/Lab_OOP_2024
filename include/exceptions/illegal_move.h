#include "base_exception.h"

namespace exceptions {

class IllegalMoveException: public BaseException {
public:
  IllegalMoveException() = default;
  IllegalMoveException(IllegalMoveException& other_exception) = default;
  IllegalMoveException& operator=(IllegalMoveException& other_exception) = default;
  const char* what() const noexcept override;
  static const bool is_fatal = false;
  ~IllegalMoveException() = default;
};

} // namespace exceptions
