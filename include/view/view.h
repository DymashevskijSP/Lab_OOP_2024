#ifndef VIEW_H_
#define VIEW_H_
#include "base_exception.h"
#include "cell.h"
#include "interface_info.h"
#include "move.h"
#include <utility>
#include <vector>

namespace view {
class View {
public: 
  virtual void draw_boards(std::vector<std::vector<sea_battle::Cell>> enemy_board, std::vector<std::vector<sea_battle::Cell>> your_board) = 0;
  virtual sea_battle::BoardCoordinates get_coordinates() = 0;
  virtual sea_battle::Move get_move() = 0;
  virtual void draw_interface(InterfaceInfo info) = 0;
  virtual void draw_exception(const exceptions::BaseException& exception) = 0;
  virtual void draw_ability_result(const std::string& result) = 0;
  virtual std::string get_save_name() = 0;
  virtual std::pair<sea_battle::BoardCoordinates, bool> get_ship(size_t size) = 0;

};

} // namespace view

#endif // VIEW_H_
