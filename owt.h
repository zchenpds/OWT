#ifndef OWT_H
#define OWT_H


#include <chrono>
#include <deque>

// Translate from pts to system timestmap using the 
// minimum measured offset from pts to system timestamps
template <typename DurationType>
class Owt
{
  struct PtsSysTime {
    DurationType pts;
    DurationType sys;
  };

  inline DurationType getOffset(const PtsSysTime & t) const {
    return t.sys - t.pts;
  }

  std::deque<PtsSysTime> deq_;
  DurationType window_size_;

public:
  Owt(DurationType window_size): window_size_(window_size) {}
  DurationType operator()(DurationType pts, DurationType sys)
  {
    PtsSysTime t{pts,sys};
    if (deq_.empty())
    {
      deq_.emplace_back(t);
      return sys;
    }

    while (deq_.size() && getOffset(deq_.back()) >= getOffset(t)) {
      deq_.pop_back();
    }
    deq_.emplace_back(t);

    DurationType res = t.pts + getOffset(deq_.front());

    if (t.pts - deq_.front().pts > window_size_) {
      deq_.pop_front();
    }
    
    return res;
  }
};

#endif // OWT_H