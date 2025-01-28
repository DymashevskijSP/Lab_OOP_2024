#ifndef SHIP_MANAGER_H_
#define SHIP_MANAGER_H_
#include "ship.h"
#include <memory>

namespace sea_battle {

class ShipManager {
public:
  ShipManager();
  ShipManager(std::vector<std::shared_ptr<Ship>> ships);
  void add_ship(size_t size);
  bool has_undestroyed_ships() const;
  std::vector<std::shared_ptr<Ship>> get_ships() const &;
  int get_undestroyed_ships_counter() const;
private:
  std::vector<std::shared_ptr<Ship>> ships;
};

} // namespace sea_battle
#endif
