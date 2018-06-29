#define HIT_LIST_CPP
#include <hit_list.hpp>
#include <hit.hpp>

#include <vector>

namespace attpcfe {

  class hit_list::hit_list_impl {

  public:
    hit_list_impl() {}

    std::vector<hit> _hits;
  };

  hit_list::hit_list() : _pimpl{new hit_list_impl{}, [](hit_list_impl* ptr){ delete ptr; }} {}

  void hit_list::add_hit(hit&& h) { _pimpl->_hits.push_back(std::move(h)); }
}

