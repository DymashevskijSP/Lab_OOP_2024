#include "abilities/scanner.h"

namespace sea_battle {

ScannerAbility::ScannerAbility(){}

std::string ScannerAbility::activate(Board& board, BoardCoordinates coordinates, std::function<void(Board&, BoardCoordinates)>&, const ShipManager&) {
  for(int dx = 0; dx <= 1; dx++) {
    for(int dy = 0; dy <= 1; dy++) {
      BoardCoordinates checked_coordinates(coordinates.x()+dx, coordinates.y()+dy);
      if (board.has_ship(checked_coordinates)) {
        return "detected ship in sector";
      }
    }
  }
  return "scanner detected no ships in sector";
}

std::string ScannerAbility::name() const {
  return "scanner";
}

Ability* ScannerAbility::clone() const {
  return new ScannerAbility(*this);
} 

} // namespace sea_battle
