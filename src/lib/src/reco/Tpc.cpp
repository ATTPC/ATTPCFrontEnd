#define TPC_CPP
#include <reco/Tpc.hpp>

namespace attpcfe {

  class Tpc::TpcImpl {

  public:
    TpcImpl(std::string geomFile) : _geomFile{std::move(geomFile)} {}

    std::string _geomFile;
    double _radius{0.};
    double _height{0.};
  };
  
  Tpc::Tpc(std::string geomFile) : _pImpl{new TpcImpl{std::move(geomFile)}, [](TpcImpl* ptr){ delete ptr; }} {}

  std::string const& Tpc::geomFile() const { return _pImpl->_geomFile; }
  double Tpc::radius() const { return _pImpl->_radius; }
  double Tpc::height() const { return _pImpl->_height; }

  void Tpc::setRadius(double radius) { _pImpl->_radius = radius; }
  void Tpc::setHeight(double height) { _pImpl->_height = height; }
}
