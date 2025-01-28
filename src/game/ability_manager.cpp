#include "ability_manager.h"
#include "ability_error.h"
#include "abilities/double_attack.h"
#include "abilities/random_attack.h"
#include "abilities/scanner.h"
#include "ship_manager.h"

namespace sea_battle {

void AbilityManager::add_ability(std::unique_ptr<Ability> new_ability) {
  ability_queue.push(std::move(new_ability));
}

void AbilityManager::add_random_ability() {
  int num = std::rand() % ABILITY_NUM;
  if(num == 0) {
    ability_queue.push(std::make_unique<DoubleAttackAbility>());
  } else if(num == 0) {
    ability_queue.push(std::make_unique<ScannerAbility>());
  } else if(num == 2) {
    ability_queue.push(std::make_unique<RandomAttackAbility>());
  }
}

std::string AbilityManager::activate_next_ability(Board& board, BoardCoordinates coordinates, std::function<void(Board&, BoardCoordinates)>& attack_callback, const ShipManager& ship_manager) {
  if (ability_queue.empty()) {
    throw exceptions::AbilityException();
  }
  std::string result = ability_queue.front()->activate(board, coordinates, attack_callback, ship_manager);
  ability_queue.pop();
  return result;
}

int AbilityManager::get_abilities_counter() const {
  return ability_queue.size();
}

std::string AbilityManager::get_next_ability_name() const {
  return ability_queue.empty() ? "no ability" : ability_queue.front()->name();
}

bool AbilityManager::is_next_targeted() const {
  return !ability_queue.empty() && ability_queue.front()->require_target();
}

std::queue<std::unique_ptr<Ability>>& AbilityManager::get_abilities() {
  return ability_queue;
}

void AbilityManager::clear() {
  std::queue<std::unique_ptr<Ability>> empty;
  std::swap(ability_queue, empty);
}

} // namespace sea_battle
