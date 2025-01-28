#include "ability.h"
#include "board.h"
#include "board_coordinates.h"
namespace sea_battle {
class ScannerAbility: public Ability { //attack makes extra damage
public:
  ScannerAbility();
  std::string activate(Board& board, BoardCoordinates coordinates, std::function<void(Board&, BoardCoordinates)>&, const ShipManager&) override;
  std::string name() const override;
  constexpr bool require_target() const override {return true;};
  Ability* clone() const override;
};
} // namespace sea_battle
