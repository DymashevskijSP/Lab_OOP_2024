#include "parameters.h"

namespace sea_battle {

Parameters::Parameters(int width, int height): width_(width), height_(height){
}

Parameters::Parameters(): width_(DEFAULT_BOARD_WIDTH), height_(DEFAULT_BOARD_HEIGHT){
}

size_t Parameters::width() {
  return width_;
}

size_t Parameters::height() {
  return height_;
}
} // namespace sea_battle
