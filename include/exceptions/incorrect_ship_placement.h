#include "base_exception.h"

namespace exceptions {

class IncorrectShipPlacementException: public BaseException {
public:
  IncorrectShipPlacementException() = default;
  IncorrectShipPlacementException(IncorrectShipPlacementException& other_exception) = default;
  IncorrectShipPlacementException& operator=(IncorrectShipPlacementException& other_exception) = default;
  const char* what() const noexcept override;
  static const bool is_fatal = false;
  ~IncorrectShipPlacementException() = default;
};

} // namespace exceptions
