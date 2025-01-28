#include "cell.h"
#include <ostream>

namespace sea_battle {

class CellInfo {
public:
  CellInfo(Cell cell_type_, int ship_num_ = -1, int ship_segment_num_ = -1);
  friend std::ostream& operator<<(std::ostream& stream, CellInfo& cell_info);
  Cell get_cell_type();
  int get_ship_num();
  int get_segment_num();

private:
  Cell cell_type;
  int ship_num;
  int ship_segment_num;
};

} // namespace sea_battle
