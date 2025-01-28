#include "abilities/random_attack.h"

namespace sea_battle {

RandomAttackAbility::RandomAttackAbility(){}

std::string RandomAttackAbility::activate(Board&, BoardCoordinates, std::function<void(Board&, BoardCoordinates)>&, const ShipManager& ship_manager) {
  std::vector<std::shared_ptr<Ship>> ships = ship_manager.get_ships();
  std::vector<std::shared_ptr<Ship>> undestroyed_ships;
  for(const auto& ship: ships) {
    if(!ship->is_destroyed()) {
      undestroyed_ships.push_back(ship);
    }
  }
  std::size_t ship_number = std::rand() % undestroyed_ships.size();
  std::size_t ship_segment = std::rand() % undestroyed_ships[ship_number]->size();
  undestroyed_ships[ship_number]->do_hit(ship_segment);
  return "random attack dealt damage";
}

std::string RandomAttackAbility::name() const {
  return "random attack";
}

Ability* RandomAttackAbility::clone() const {
  return new RandomAttackAbility(*this);
} 

} // namespace sea_battle
