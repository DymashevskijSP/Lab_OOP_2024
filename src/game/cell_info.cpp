#include "cell_info.h"

namespace sea_battle {
  
CellInfo::CellInfo(Cell cell_type_, int ship_num_, int ship_segment_num_): cell_type(cell_type_), ship_num(ship_num_), ship_segment_num(ship_segment_num_) {}

std::ostream& operator << (std::ostream& stream, CellInfo& cell_info) {
  stream.write(reinterpret_cast<const char *>(&cell_info.cell_type), sizeof(cell_info.cell_type));
  stream.write(reinterpret_cast<const char *>(&cell_info.ship_num), sizeof(cell_info.ship_num));
  stream.write(reinterpret_cast<const char *>(&cell_info.ship_segment_num), sizeof(cell_info.ship_segment_num));
  return stream;
}

Cell CellInfo::get_cell_type() {
  return cell_type;
}

int CellInfo::get_ship_num() {
  return ship_num;
}

int CellInfo::get_segment_num() {
  return ship_segment_num;
}

} // namespace sea_battle
