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

    //void set_cobo(int16_t cobo);
    //void set_asad(int16_t asad);
    //void set_aget(int16_t aget);
    //void set_channel(int16_t channel);
    //void set_number(int16_t number);
    //void set_adcs(int16_t* f, int16_t* l);
    void SetRawData(std::vector<int16_t>&& rawData);
    int16_t Cobo() const;
  };
}
#endif
