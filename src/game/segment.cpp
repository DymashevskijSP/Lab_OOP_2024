#include <utility>
#include "segment.h"
namespace sea_battle {
  
Segment::Segment(): state(SegmentState::FULL) {
}
  
Segment::Segment(const Segment& segment): state(segment.state) {
}
  
Segment::Segment(Segment&& segment): state(std::move(segment.state)) {
}

Segment& Segment::operator=(const Segment& segment) noexcept {
  state=segment.state;
  return *this;
}

Segment& Segment::operator=(Segment&& segment) noexcept {
  state = std::move(segment.state);
  return *this;
}
SegmentState Segment::get_state() const noexcept {
  return state;
}
void Segment::do_hit() {
  if (state == SegmentState::FULL) {
    state = SegmentState::DAMAGED;
  } else if (state == SegmentState::DAMAGED) {
    state = SegmentState::DESTROYED;
  }
}

bool Segment::is_destroyed() const noexcept {
  return state == SegmentState::DESTROYED;
}

} //namespace sea_battle
