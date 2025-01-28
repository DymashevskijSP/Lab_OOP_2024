#ifndef BOARD_H_
#define BOARD_H_
#include "board_coordinates.h"
#include "cell.h"
#include "ship.h"
#include <memory>
#include <variant>
#include <vector>

namespace sea_battle {

enum class Direction { VERTICAL, HORIZONTAL };

class Board {
public:
  using board_ship_type = std::pair<std::shared_ptr<Ship>, size_t>; 
  using board_cell_type = std::variant<Cell, board_ship_type>;

  Board(std::vector<std::vector<board_cell_type>> content); 
  Board(size_t width, size_t height, bool is_ally);

  Board(const Board &board);

  Board(Board &&board);

  Board &operator=(const Board &board) noexcept;

  Board &operator=(Board &&board) noexcept;

  ~Board() = default;

  std::pair<std::shared_ptr<Ship>, size_t> do_hit(BoardCoordinates coordinates);
  
  void place_ship(std::shared_ptr<Ship> ship, Direction direction,
                  BoardCoordinates coordinates);
  
  std::vector<std::vector<Cell>> get_view();
  
  void place_ship_segment_view(BoardCoordinates coordinates, bool is_destroyed);

  bool has_ship(BoardCoordinates coordinates) const noexcept;
  std::vector<std::vector<board_cell_type>> get_content() const & noexcept;
  size_t get_width() const &;
  size_t get_height() const &;

private:
    
  bool check_ship_coordinates(BoardCoordinates coordinates, Direction direction,
                              size_t size) const noexcept;
  
  bool is_coordinates_correct(int x, int y) const noexcept;
  
  std::vector<std::vector<board_cell_type>> content;
  
  size_t width;
  
  size_t height;

};

} // namespace sea_battle

#endif // BOARD_H_
