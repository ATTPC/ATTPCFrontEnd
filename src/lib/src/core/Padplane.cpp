#define PADPLANE_CPP
#include <core/Padplane.hpp>

#include <fstream>
#include <sstream>
#include <cmath>

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

    this->load();
  }

  std::string const& Padplane::geomFile() const { return _pImpl->_geomFile; }
  double Padplane::sPadSize() const { return _pImpl->_sPadSize; }
  double Padplane::lPadSize() const { return _pImpl->_lPadSize; }
  std::vector<std::pair<double, double>>& Padplane::sPadCoords() { return _pImpl->_sPadCoords; }
  std::vector<std::pair<double, double>>& Padplane::lPadCoords() { return _pImpl->_lPadCoords; }
  std::vector<std::size_t>& Padplane::orientations() { return _pImpl->_orientations; }

  std::pair<double, double> const& Padplane::padCoords(std::size_t padNum) const
  {
    if (_pImpl->_sPadCoords[padNum].first == 0.)
      return _pImpl->_lPadCoords[padNum];
    else return _pImpl->_sPadCoords[padNum];
  }

  void Padplane::load()
  {
    std::ifstream in{_pImpl->_geomFile};

    std::size_t padNum;
    double x_0, x_1;
    double y_0, y_1;
    std::string line;
    while (std::getline(in, line))
    {
      std::istringstream s{line};
      s >> padNum >> x_0 >> y_0 >> x_1 >> y_1;

      auto x = 0.;
      auto y = 0.;
      
      if (y_1 > y_0) _pImpl->_orientations[padNum] = 1;
      
      if ((x_1 - x_0) < _pImpl->_sPadSize)
      {
	x = x_0 + _pImpl->_sPadSize / 2;
	(y_1 > y_0) ? y = y_0 + _pImpl->_sPadSize * std::sqrt(3) / 4 : y = y_0 - _pImpl->_sPadSize * std::sqrt(3) / 4;
	_pImpl->_sPadCoords[padNum] = {x, y};
      }
      else
      {
	x = x_0 + _pImpl->_lPadSize / 2;
	(y_1 > y_0) ? y = y_0 + _pImpl->_lPadSize * std::sqrt(3) / 4 : y = y_0 - _pImpl->_lPadSize * std::sqrt(3) / 4;
	_pImpl->_lPadCoords[padNum] = {x, y};
      }
    }
  }
  
}
