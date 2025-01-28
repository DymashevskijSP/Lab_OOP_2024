#include "view.h"

namespace view {

class TestView : public View {
public:
  void draw_boards(std::vector<std::vector<sea_battle::Cell>> enemy_board, std::vector<std::vector<sea_battle::Cell>> your_board) override;
  sea_battle::Move get_move() override;
  sea_battle::BoardCoordinates get_coordinates() override;
  void draw_interface(InterfaceInfo info) override;
  void draw_exception(const exceptions::BaseException& e) override;
  void draw_ability_result(const std::string& result) override;
  std::string get_save_name() override;
  std::pair<sea_battle::BoardCoordinates, bool> get_ship(size_t size) override;
};

} // namespace view
