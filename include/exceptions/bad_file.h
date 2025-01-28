#include "base_exception.h"

namespace exceptions {

class BadFileException: public BaseException {
public:
  BadFileException() = default;
  BadFileException(BadFileException& other_exception) = default;
  BadFileException& operator=(BadFileException& other_exception) = default;
  const char* what() const noexcept override;
  static const bool is_fatal = false;
  ~BadFileException() = default;
};

} // namespace exceptions
