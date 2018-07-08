#define GUISTATE_CPP
#include <gui/GuiState.hpp>
//#include <OSMMap.hpp>

namespace attpcfe {

  class GuiState::GuiStateImpl {

  public:
    GuiStateImpl() {}

    //udmx::osm::Map _map;
  };

  GuiState::GuiState() : _pImpl{new GuiStateImpl{}, [](GuiStateImpl* ptr){ delete ptr; }} {}

  //void GuiState::setMap(udmx::osm::Map&& map) { _pImpl->_map = std::move(map); }
  //udmx::osm::Map& GuiState::map() { return _pImpl->_map; }
}
