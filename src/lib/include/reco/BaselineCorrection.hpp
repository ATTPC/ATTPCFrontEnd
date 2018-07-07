#ifndef BASELINECORRECTION_HPP
#define BASELINECORRECTION_HPP

namespace attpcfe
{
  class Pad;
  class BLCorrection {

  public:
    void SubtractBaseline(Pad& pad);
  };
}
#endif
