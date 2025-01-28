#include "ability.h"
#include "board.h"
#include "board_coordinates.h"

namespace sea_battle {

class DoubleAttackAbility: public Ability { //attack makes extra damage
public:
  DoubleAttackAbility();
  std::string activate(Board&, BoardCoordinates, std::function<void(Board&, BoardCoordinates)>& callback, const  ShipManager&) override;
  std::string name() const override;
  Ability* clone() const override;
};

} // namespace sea_battle
