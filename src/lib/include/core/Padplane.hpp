#ifndef PADPLANE_HPP
#define PADPLANE_HPP

#include <memory>
#include <string>
#include <vector>

class vtkPlot;

namespace attpcfe {

  class Padplane {

    class PadplaneImpl;
    std::unique_ptr<PadplaneImpl, void(*)(PadplaneImpl*)> _pImpl;

  public:
    explicit Padplane(std::string geomFile);

    std::string const& geomFile() const;
    std::size_t nPads() const;
    bool padIsUp(std::size_t padNum) const;
    bool padIsSmall(std::size_t padNum) const;
    double padSize(std::size_t padNum) const;
    double padHeight(std::size_t padNum) const;
    std::pair<double, double> const& padCoords(std::size_t padNum) const;
    std::vector<vtkPlot*>& litPads();
    void load();
  };
}
#endif
