#ifndef RAWTRACK_HPP
#define RAWTRACK_HPP

#include <memory>

namespace attpcfe {

  class RawTrack {

    class RawTrackImpl;
    std::unique_ptr<RawTrackImpl, void(*)(RawTrackImpl*)> _pImpl;

  public:
    RawTrack();
  };
}
#endif
