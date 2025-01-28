#include "base_exception.h"
#include <string>

namespace exceptions {

class IncorrectCoordinatesException: public BaseException {
public:
  IncorrectCoordinatesException();
  IncorrectCoordinatesException(int x, int y);
  IncorrectCoordinatesException(IncorrectCoordinatesException& other_exception);
  IncorrectCoordinatesException operator=(IncorrectCoordinatesException& other);
  const char* what() const noexcept override;
  static const bool is_fatal = false;
private:
  int x = 0;
  int y = 0;
  std::string what_message;
};

} // namespace exceptions
