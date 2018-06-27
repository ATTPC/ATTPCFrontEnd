#ifndef PAD_HPP
#define PAD_HPP

#include <memory>
#include <vector>

namespace attpcfe {


  class pad {

    class pad_impl;
    std::unique_ptr<pad_impl, void(*)(pad_impl*)> _pimpl;

  public:
    pad();

    //void set_cobo(int16_t cobo);
    //void set_asad(int16_t asad);
    //void set_aget(int16_t aget);
    //void set_channel(int16_t channel);
    //void set_number(int16_t number);
    //void set_adcs(int16_t* f, int16_t* l);
    void set_raw_data(std::vector<int16_t>&& raw_data);
    int16_t cobo() const;
  };
}
#endif
