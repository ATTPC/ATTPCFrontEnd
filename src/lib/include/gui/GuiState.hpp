#ifndef GUISTATE_HPP
#define GUISTATE_HPP

#include <memory>

namespace attpcfe {

  class GuiState {

    class GuiStateImpl;
    std::unique_ptr<GuiStateImpl, void(*)(GuiStateImpl*)> _pImpl;
    
    //GuiState();

  public:
    GuiState();
    GuiState(GuiState const&) = delete;
    GuiState& operator=(GuiState const&) = delete;

    //static GuiState& instance()
    //{
    //  static GuiState _state;
    //  return _state;
    //}

    //void setMap(udmx::osm::Map&& map);
    //udmx::osm::Map& map();
  };
}
#endif
