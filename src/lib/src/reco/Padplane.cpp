#define PADPLANE_CPP
#include <reco/Padplane.hpp>

namespace attpcfe {

  class Padplane::PadplaneImpl {

  public:
    PadplaneImpl(std::string geomFile) : _geomFile{std::move(geomFile)} {}

    std::string _geomFile;
    std::size_t _nPads{10240};
    double _sPadSize{4.6737};
    double _lPadSize{9.5818};
    std::vector<std::pair<double, double>> _sPadCoords{_nPads, {0., 0.}};
    std::vector<std::pair<double, double>> _lPadCoords{_nPads, {0., 0.}};
    std::vector<std::size_t> _orientations;
  };
  
  Padplane::Padplane(std::string geomFile) : _pImpl{new PadplaneImpl{std::move(geomFile)}, [](PadplaneImpl* ptr){ delete ptr; }}
  {
    _pImpl->_orientations.reserve(_pImpl->_nPads);
    _pImpl->_orientations.assign(_pImpl->_nPads, 0);
  }

  std::string const& Padplane::geomFile() const { return _pImpl->_geomFile; }
  double Padplane::sPadSize() const { return _pImpl->_sPadSize; }
  double Padplane::lPadSize() const { return _pImpl->_lPadSize; }
  std::vector<std::pair<double, double>>& Padplane::sPadCoords() { return _pImpl->_sPadCoords; }
  std::vector<std::pair<double, double>>& Padplane::lPadCoords() { return _pImpl->_lPadCoords; }
  std::vector<std::size_t>& Padplane::orientations() { return _pImpl->_orientations; }
}
