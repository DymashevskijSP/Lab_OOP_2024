#include "board.h"
#include "incorrect_ship_placement.h"
#include "incorrect_coordinates.h"
#include <utility>

namespace sea_battle {

bool Board::is_coordinates_correct(int x, int y) const noexcept {
  return x >= 0 && y >= 0 && static_cast<size_t>(x) < width && static_cast<size_t>(y) < height;
}

bool Board::check_ship_coordinates(BoardCoordinates coordinates, Direction direction, size_t size) const noexcept {
  //checks place for ship
  int x = coordinates.x();
  int y = coordinates.y();
  for (size_t i = 0; i < size; i++) {
    if (!is_coordinates_correct(x, y)) {
      return false;
    }
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (is_coordinates_correct(x+dx, y+dy) && std::holds_alternative<Board::board_ship_type>(content[x + dx][y + dy])) {
            return false;
        }
      }
    }
    if (direction == Direction::VERTICAL) {
      y++;
    } else if (direction == Direction::HORIZONTAL) {
      x++;
    }
  }
  return true;
}

bool Board::has_ship(BoardCoordinates coordinates) const  noexcept { // no exception
  return is_coordinates_correct(coordinates.x(), coordinates.y()) && std::holds_alternative<Board::board_ship_type>(content[coordinates.x()][coordinates.y()]);
}

Board::Board(size_t width_, size_t height_, bool is_visible): 
  content(std::vector<std::vector<Board::board_cell_type>>(
    width_, std::vector<Board::board_cell_type>(
      height_, is_visible ? Cell::UNKNOWN : Cell::UNKNOWN
      )
    )), 
  width(width_), 
  height(height_) {
};

size_t Board::get_width() const & {
  return width;
}

size_t Board::get_height() const & {
  return height;
}

Board::Board(const Board& board): content(board.content), width(board.width), height(board.height) {
}

Board::Board(Board&& board): content(std::move(board.content)), width(std::move(board.width)), height(std::move(board.height)) {
}

Board::Board(std::vector<std::vector<board_cell_type>> board): content(board), width(board.size()), height(board.size() > 0 ? board[0].size() : 0) {
}

Board& Board::operator=(const Board& board) noexcept {
  content = board.content;
  width = board.width;
  height = board.height;
  return *this;
}

Board& Board::operator=(Board&& board) noexcept {
  content = board.content;
  width = board.width;
  height = board.height;
  return *this;
}

void Board::place_ship(std::shared_ptr<Ship> ship, Direction direction, BoardCoordinates coordinates) {
  if (check_ship_coordinates(coordinates, direction, ship->size())) {
    int x = coordinates.x();
    int y = coordinates.y();
    for(size_t i = 0; i < ship->size(); i++) {
      content[x][y] = std::pair(ship, i); 
      if (direction == Direction::HORIZONTAL) {
        x++;
      } else if (direction == Direction::VERTICAL) {
        y++;
      }
    }
  } else {
    throw exceptions::IncorrectShipPlacementException(); 
  }
}

std::vector<std::vector<Board::board_cell_type>> Board::get_content() const & noexcept{
  return content;
}

std::vector<std::vector<Cell>> Board::get_view() {
  std::vector<std::vector<Cell>> result(height, std::vector<Cell>(width));
  for(size_t x = 0; x < width; x++) {
    for(size_t y = 0; y < height; y++) { 
      if (std::holds_alternative<Cell>(content[x][y])){
        result[y][x] = std::get<Cell>(content[x][y]);
      } else {
        auto [ship, num] =  std::get<Board::board_ship_type>(content[x][y]);
        result[y][x] = ship->is_segment_destroyed(num) ? Cell::DESTROYED : Cell::SHIP;
      }
    }
  }
  return result;
} 

std::pair<std::shared_ptr<Ship>, size_t> Board::do_hit(BoardCoordinates coordinates) {
  if (is_coordinates_correct(coordinates.x(), coordinates.y())) {
    if (std::holds_alternative<Board::board_ship_type>(content[coordinates.x()][coordinates.y()])) {
      return std::get<Board::board_ship_type>(content[coordinates.x()][coordinates.y()]);
    }
    content[coordinates.x()][coordinates.y()] = Cell::EMPTY;
  } else {
    throw exceptions::IncorrectCoordinatesException(coordinates.x(), coordinates.y());
  }
  return {nullptr, 0};
}

void Board::place_ship_segment_view(BoardCoordinates coordinates, bool is_destroyed) {
 if (is_coordinates_correct(coordinates.x(), coordinates.y())) {
   content[coordinates.x()][coordinates.y()] = is_destroyed ? Cell::DESTROYED : Cell::SHIP;
 } 
}
} // namespace sea_battle
