#ifndef ABILITY_MANAGER_H_
#define ABILITY_MANAGER_H_
#include "ability.h"
#include <queue>
#include <functional>
namespace sea_battle {
class AbilityManager {
public:
  void add_ability(std::unique_ptr<Ability> new_ability);
  void add_random_ability();
  std::string activate_next_ability(Board&, BoardCoordinates, std::function<void(Board&, BoardCoordinates)>&, const ShipManager&);
  std::string get_next_ability_name() const;
  int get_abilities_counter() const;
  bool is_next_targeted() const;
  std::queue<std::unique_ptr<Ability>>& get_abilities();
  void clear();
private:
  static const int ABILITY_NUM = 3;
  std::queue<std::unique_ptr<Ability>> ability_queue;

};
} // namespace sea_battle
#endif
