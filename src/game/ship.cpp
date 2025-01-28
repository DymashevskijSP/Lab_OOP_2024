#include "ship.h"

namespace sea_battle {

size_t Ship::size() const noexcept {
  return ship_content.size();
}

Ship::Ship(size_t size): ship_content(std::vector<Segment>(size <= MAX_SIZE ? size : MAX_SIZE)) {
}

Ship::Ship(const Ship& ship) {
  ship_content = ship.ship_content;
}

Ship::Ship() {
}

Ship::Ship(const std::vector<Segment> segments): ship_content(segments){
}

Ship::Ship(Ship&& ship): ship_content(std::move(ship.ship_content)){
}

Ship& Ship::operator=(const Ship& ship) noexcept {
    ship_content = ship.ship_content;
    return *this;
}

Ship& Ship::operator=(Ship&& ship) noexcept {
  ship_content = std::move(ship.ship_content);
  return *this;
}

void Ship::do_hit(size_t segment_number) {
  if (segment_number < ship_content.size()) {
    ship_content[segment_number].do_hit();
  }
}

bool Ship::is_destroyed() const noexcept {
  for (const auto& segment: ship_content) {
    if (!segment.is_destroyed()) {
      return false;
    }
  }
  return true;
}
std::vector<Segment> Ship::get() const noexcept {
  return ship_content;
}
bool Ship::is_segment_destroyed (size_t segment_number) const {
  return ship_content[segment_number].is_destroyed();
}

} // namespace sea_battle
