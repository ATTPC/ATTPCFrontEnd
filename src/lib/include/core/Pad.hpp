#ifndef PAD_HPP
#define PAD_HPP

#include <memory>
#include <vector>

namespace attpcfe {


  class Pad {

    class PadImpl;
    std::unique_ptr<PadImpl, void(*)(PadImpl*)> _pImpl;

  public:
    Pad();

    void SetRawData(std::vector<int16_t> rawData);
    std::vector<int16_t> const& RawData() const;
    std::vector<double>& Data();
    int16_t Cobo() const;
    int16_t Asad() const;
    int16_t Aget() const;
    int16_t Channel() const;
    int16_t Number() const;
  };
}
#endif
