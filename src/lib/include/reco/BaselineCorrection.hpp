#ifndef BASELINECORRECTION_HPP
#define BASELINECORRECTION_HPP

namespace attpcfe
{
  class Pad;
  class BLCorrection {

  public:
    void subtractBaseline(Pad& pad);
  };
}
#endif
