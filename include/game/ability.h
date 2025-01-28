#ifndef ABILITY_H_
#define ABILITY_H_
#include "board.h"
#include "board_coordinates.h"
#include "ship_manager.h"
#include <functional>

namespace sea_battle{

class Ability {
public:
  virtual std::string activate(Board& board, BoardCoordinates coordinates, std::function<void(Board&, BoardCoordinates)>& attack_callback, const ShipManager& ship_manager) = 0;
  virtual std::string name() const = 0;
  virtual constexpr bool require_target() const { return false; }
  virtual Ability* clone() const = 0;
};

} // namespace sea_battle
#endif
