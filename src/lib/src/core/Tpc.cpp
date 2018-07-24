#define TPC_CPP
#include <core/Tpc.hpp>

#include <fstream>
#include <sstream>

namespace attpcfe {

  class Tpc::TpcImpl {

  public:
    TpcImpl(std::string geomFile) : _geomFile{std::move(geomFile)} {}

    std::string _geomFile;
    double _radius{0.};
    double _height{0.};
    double _driftVelocity{5.2E6}; // cm/s
    double _samplingFreq{12.5E6}; // Hz
    int _entryBucket{280};
  };
  
  Tpc::Tpc(std::string geomFile) : _pImpl{new TpcImpl{std::move(geomFile)}, [](TpcImpl* ptr){ delete ptr; }}
  {
    this->load();
  }

  std::string const& Tpc::geomFile() const { return _pImpl->_geomFile; }
  double Tpc::radius() const { return _pImpl->_radius; }
  double Tpc::height() const { return _pImpl->_height; }
  double Tpc::driftVelocity() const { return _pImpl->_driftVelocity; }
  double Tpc::samplingFreq() const { return _pImpl->_samplingFreq; }
  int Tpc::entryBucket() const { return _pImpl->_entryBucket; }

  void Tpc::load() {

    std::ifstream in{_pImpl->_geomFile};

    auto radius = 0.;
    auto height = 0.;
    std::string line;
    while (std::getline(in, line))
    {
      std::istringstream s{line};
      s >> radius >> height;
      
      _pImpl->_radius = radius;
      _pImpl->_height = height;
    }
  }
  
}
