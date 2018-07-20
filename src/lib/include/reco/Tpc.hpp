#ifndef TPC_HPP
#define TPC_HPP

#include <memory>
#include <string>
#include <vector>

namespace attpcfe {

  class Tpc {

    class TpcImpl;
    std::unique_ptr<TpcImpl, void(*)(TpcImpl*)> _pImpl;

  public:
    explicit Tpc(std::string geomFile);

    std::string const& geomFile() const;
    double radius() const;
    double height() const;
    void setRadius(double radius);
    void setHeight(double height);
  };
}
#endif
