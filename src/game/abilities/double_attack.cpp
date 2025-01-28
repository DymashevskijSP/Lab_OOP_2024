#include "abilities/double_attack.h"
namespace sea_battle {

DoubleAttackAbility::DoubleAttackAbility(){}

std::string DoubleAttackAbility::activate(Board&, BoardCoordinates, std::function<void(Board&, BoardCoordinates)>& callback, const ShipManager&) {
  callback = [](Board& board, BoardCoordinates coordinates) {
    auto [ship, num] = board.do_hit(coordinates);
    if(ship) {
      ship->do_hit(num);
    }
  };
  return "double attack activated";
}

std::string DoubleAttackAbility::name() const {
  return "double attack";
}

Ability* DoubleAttackAbility::clone() const {
  return new DoubleAttackAbility(*this);
} 

} // namespace sea_battle
