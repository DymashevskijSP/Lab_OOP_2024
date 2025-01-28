#include "ability.h"

namespace sea_battle {

class RandomAttackAbility: public Ability { //attack makes extra damage
public:
  RandomAttackAbility();
  std::string activate(Board& board, BoardCoordinates coordinates, std::function<void(Board&, BoardCoordinates)>&, const ShipManager& ship_manager) override;
  std::string name() const override;
  Ability* clone() const override;
};

} // namespace sea_battle
