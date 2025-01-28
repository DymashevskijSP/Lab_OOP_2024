#ifndef PARAMETERS_H_
#define PARAMETERS_H_
#include <cstddef>
namespace sea_battle {
class Parameters {
  static const int DEFAULT_BOARD_WIDTH = 10;
  static const int DEFAULT_BOARD_HEIGHT = 10;
  size_t width_;
  size_t height_;
public:
  size_t width();
  size_t height();
  Parameters();
  Parameters(int width_, int height_);
};
} // namespace sea_battle
#endif // PARAMETERS_H_
