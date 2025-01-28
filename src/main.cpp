#include "game_controller.h"
#include "parameters.h"
#include "test_view.h"

#include <iostream>

void start_game(sea_battle::Parameters parameters) {
  view::View *view = new view::TestView();
  sea_battle::GameController controller(parameters, view);
  controller.start_game();
}

int main() { 
  try {
    start_game(sea_battle::Parameters(4, 4)); 
  } catch (std::exception& e) {
    std::cerr<<"unexpected error, terminating\n" << e.what();
  }
}
