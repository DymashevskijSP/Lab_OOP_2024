#ifndef SEGMENT_H_
#define SEGMENT_H_
namespace sea_battle {

enum class SegmentState {FULL, DAMAGED, DESTROYED};

class Segment{
private:
  SegmentState state;
public:
  Segment();
  
  Segment(Segment&& segment);
  
  Segment(const Segment& segment);
  
  Segment& operator=(const Segment& segment) noexcept;
  
  Segment& operator=(Segment&& segment) noexcept;
  
  ~Segment() = default;
  SegmentState get_state() const noexcept;
  void do_hit();
  bool is_destroyed() const noexcept;
};

} // namespace sea_battle
#endif // SEGMENT_H_
