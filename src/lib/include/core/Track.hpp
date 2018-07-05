#ifndef TRACK_HPP
#define TRACK_HPP

#include <memory>

namespace attpcfe {

  class Track {

    class TrackImpl;
    std::unique_ptr<TrackImpl, void(*)(TrackImpl*)> _pImpl;

  public:
    Track();
  };
}
#endif
