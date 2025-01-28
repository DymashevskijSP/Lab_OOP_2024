#include "base_exception.h"

namespace exceptions {

class AbilityException: public BaseException {
public:
  AbilityException() = default;
  AbilityException(AbilityException& other_exception) = default;
  AbilityException& operator=(AbilityException& other_exception) = default;
  const char* what() const noexcept override;
  static const bool is_fatal = false;
  ~AbilityException() = default;
};

} // namespace exceptions
