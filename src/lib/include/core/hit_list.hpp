#ifndef HIT_LIST_HPP
#define HIT_LIST_HPP

#include <memory>

namespace attpcfe {

  class hit;
  class hit_list {

    class hit_list_impl;
    std::unique_ptr<hit_list_impl, void(*)(hit_list_impl*)> _pimpl;

  public:
    hit_list();

    void add_hit(hit&& h);
  };
}
#endif
