#include "incorrect_coordinates.h"

namespace exceptions {

IncorrectCoordinatesException::IncorrectCoordinatesException(int x_, int y_): x(x_), y(y_) {
  what_message= std::string("incorrect coordinates: " + std::to_string(x) + "," + std::to_string(y));
}

IncorrectCoordinatesException::IncorrectCoordinatesException(IncorrectCoordinatesException& other): x(other.x), y(other.y) {
  what_message= std::string("incorrect coordinates: " + std::to_string(x) + "," + std::to_string(y));
}

IncorrectCoordinatesException IncorrectCoordinatesException::operator=(IncorrectCoordinatesException& other) {
  x = other.x;
  y = other.y;
  what_message= std::string("incorrect coordinates: " + std::to_string(x) + "," + std::to_string(y));
  return *this;
}

const char* IncorrectCoordinatesException::what() const noexcept {
  return what_message.c_str();
}

} // namespace exceptions
