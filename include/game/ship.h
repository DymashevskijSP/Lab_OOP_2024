#ifndef SHIP_H_
#define SHIP_H_
#include <vector>
#include "segment.h"

namespace sea_battle {

class Ship {
private:
  std::vector<Segment> ship_content;
  static const size_t MAX_SIZE = 4;
public:
  explicit Ship(size_t size);
  Ship();
  Ship(Ship&& ship);
  Ship(const std::vector<Segment> segments);
  Ship(const Ship& ship);
  Ship& operator=(const Ship& ship) noexcept;
  Ship& operator=(Ship&& ship) noexcept;
  ~Ship() = default;
  void do_hit(size_t segment_number);
  size_t size() const noexcept;
  bool is_destroyed() const noexcept;
  std::vector<Segment> get() const noexcept;
  bool is_segment_destroyed(size_t segment_number) const;
};

} // namespace sea_battle
#endif // SHIP_H_
