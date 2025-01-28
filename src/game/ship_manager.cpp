#include "ship_manager.h"
namespace sea_battle {

ShipManager::ShipManager(){
}

ShipManager::ShipManager(std::vector<std::shared_ptr<Ship>> ships_): ships(ships_) {
}

void ShipManager::add_ship(size_t size) {
  std::shared_ptr<Ship> ship_ptr(new Ship(size));
  ships.push_back(ship_ptr);
}

bool ShipManager::has_undestroyed_ships() const {
  return get_undestroyed_ships_counter() != 0;
}

std::vector<std::shared_ptr<Ship>> ShipManager::get_ships() const & {
  return ships;
}

int ShipManager::get_undestroyed_ships_counter() const {
  int counter = 0;
  for (const auto& ship: ships) {
    if (!ship->is_destroyed()) {
      counter++;;
    }
  }
  return counter;
}

} // namespace sea_battle
