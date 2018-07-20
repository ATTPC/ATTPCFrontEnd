#ifndef PADPLANE_HPP
#define PADPLANE_HPP

#include <memory>
#include <string>
#include <vector>

namespace attpcfe {

  class Padplane {

    class PadplaneImpl;
    std::unique_ptr<PadplaneImpl, void(*)(PadplaneImpl*)> _pImpl;

  public:
    explicit Padplane(std::string geomFile);

    std::string const& geomFile() const;
    double sPadSize() const;
    double lPadSize() const;
    std::vector<std::pair<double, double>>& sPadCoords();
    std::vector<std::pair<double, double>>& lPadCoords();
    std::vector<std::size_t>& orientations();
  };
}
#endif
