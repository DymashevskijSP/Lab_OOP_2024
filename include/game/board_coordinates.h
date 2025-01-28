#ifndef BOARD_COORDINATES_H_
#define BOARD_COORDINATES_H_
#include <cstddef>
namespace sea_battle {

class BoardCoordinates {
private:
  size_t x_;
  size_t y_;

public:
  BoardCoordinates(size_t x, size_t y);
  size_t x() const &;
  size_t y() const &;
};

} // namespace sea_battle
#endif // BOARD_COORDINATES_H_
