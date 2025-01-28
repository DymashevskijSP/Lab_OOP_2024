#include "test_view.h"
#include "board.h"
#include "illegal_move.h"
#include <iostream>

namespace view {

void TestView::draw_boards(std::vector<std::vector<sea_battle::Cell>> enemy_board, std::vector<std::vector<sea_battle::Cell>> ally_board) {
  
  for (size_t i = 0; i < enemy_board.size(); i++) {
    auto enemy_line = enemy_board[i];
    for(const auto cell: enemy_line) {  
      if (cell == sea_battle::Cell::UNKNOWN) {
        std::cout << '.';
      } else if (cell == sea_battle::Cell::EMPTY) {
          std::cout << '0';
      } else  if (cell == sea_battle::Cell::SHIP) {
        std::cout << 'x';
      } else if (cell == sea_battle::Cell::DESTROYED) {
        std::cout << "\033[31m"<< 'x' << "\033[39m";
      }
    }
    std::cout << " | ";
    auto ally_line = ally_board[i];
    for(const auto cell: ally_line) {  
      if (cell == sea_battle::Cell::UNKNOWN) {
        std::cout << '.';
      } else if (cell == sea_battle::Cell::EMPTY) {
          std::cout << '0';
      } else  if (cell == sea_battle::Cell::SHIP) {
        std::cout << 'x';
      } else if (cell == sea_battle::Cell::DESTROYED) {
        std::cout << "\033[31m"<< 'x' << "\033[39m";
      }
    }
    std::cout<<std::endl;
  }
}

void TestView::draw_interface(InterfaceInfo info) {
  std::cout << "undestroyed_ships: " << info.get_ships() << std::endl;
  std::cout << "you have " << info.get_abilities() << " abilities" << std::endl;
  std::cout << "current ability: " << info.get_ability_name() << std::endl;
}

sea_battle::BoardCoordinates TestView::get_coordinates() {
  int x;
  int y;
  std::cout << "enter coordinates" << std::endl;
  if (!(std::cin>>x) || !(std::cin >> y)) {
    std::cin.clear();
    std::string tmp;
    std::getline(std::cin, tmp);
    throw exceptions::IllegalMoveException();
  }
  return sea_battle::BoardCoordinates(x, y);
}

sea_battle::Move TestView::get_move() {
  std::cout << "enter \"move\" for attack or \"ability\" to activate ability" << std::endl;
  std::string move_type;
  std::cin >> move_type;
  if (move_type == "move") {
   return sea_battle::Move(sea_battle::MoveType::ATTACK, get_coordinates());
  } else if (move_type == "ability") {
    return sea_battle::Move(sea_battle::MoveType::ABILITY, sea_battle::BoardCoordinates(0, 0));
  } else if (move_type == "quit") {
    return sea_battle::Move(sea_battle::MoveType::QUIT, sea_battle::BoardCoordinates(0, 0));
  } else if (move_type == "save") {
    return sea_battle::Move(sea_battle::MoveType::SAVE, sea_battle::BoardCoordinates(0, 0));
  } else if (move_type == "load") {
    return sea_battle::Move(sea_battle::MoveType::LOAD, sea_battle::BoardCoordinates(0, 0));
  } else {
    throw exceptions::IllegalMoveException();
  }
}

void TestView::draw_exception(const exceptions::BaseException& e) {
  std::cout << "\033[31m"<< e.what() << "\033[39m" <<std::endl;
}

std::string TestView::get_save_name() {
  std::string name;
  std::cout << "enter save name" << std::endl;
  std::cin >> name;
  return name;
}

void TestView::draw_ability_result(const std::string& result) {
  std::cout << "\033[34m"<< result << "\033[39m" << std::endl;
}

std::pair<sea_battle::BoardCoordinates, bool> TestView::get_ship(size_t size) {
    int x = 0;
    int y = 0;
    std::cout << "place ship with size " << size << std::endl;
    std::cout << "Enter coordinates for ship" << std::endl;
    std::cout << "and \"v\" or \"h\" for ship direction" << std::endl;
    char dir = 'v';
    bool direction;
    if (!(std::cin>>x) || !(std::cin >> y) || !(std::cin>>dir)) {
      std::cin.clear();
      std::string tmp;
      std::getline(std::cin, tmp);
      throw exceptions::IllegalMoveException();
    }
    if (dir == 'v') {
      direction = true;
    } else if (dir == 'h') {
      direction = false;
    } else {
      throw exceptions::IllegalMoveException();
    }
    return {sea_battle::BoardCoordinates(x, y), direction};
  
}

} // namespace view
