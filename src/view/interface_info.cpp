#include "interface_info.h"
namespace view {

InterfaceInfo::InterfaceInfo (int ships_counter_, int ability_counter_, std::string next_ability_name_): 
  ships_counter(ships_counter_), 
  ability_counter(ability_counter_),
  next_ability_name(next_ability_name_) {
} 

int InterfaceInfo::get_ships() const {
  return ships_counter;
}

int InterfaceInfo::get_abilities() const {
  return ability_counter;
}

std::string InterfaceInfo::get_ability_name() const {
  return next_ability_name;
}

} // namespace view
