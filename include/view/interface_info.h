#ifndef INTERFACE_INFO_H_
#define INTERFACE_INFO_H_
#include <string>

namespace view {

class InterfaceInfo {
private:
  int ships_counter;
  int ability_counter;
  std::string next_ability_name;
public:
  InterfaceInfo(int ships_counter_, int ability_counter_, std::string next_ability_name_);
  int get_ships() const;
  int get_abilities() const;
  std::string get_ability_name() const;
};

}//namespace view

#endif
