#ifndef BASE_EXCEPTION_H_
#define BASE_EXCEPTION_H_

#include <exception>

namespace exceptions {

class BaseException : std::exception {
public:
  const char* what() const noexcept override = 0;
  static const bool is_fatal = false;
};

} // namespace exceptions
#endif
