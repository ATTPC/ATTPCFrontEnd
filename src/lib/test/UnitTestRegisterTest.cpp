#include <utils/UnitTestRegister.hpp>
#include <utils/Logger.hpp>
#include <core/Hdf5Wrapper.hpp>
#include <iostream>

using namespace attpcfe;

class A {

public:
  void print() const { std::cout << "A::print " << _val << '\n'; }
  void add(double val) { _val += val; std::cout << "A::add " << _val << '\n'; }

private:
  double _val{0.};
};


int main() {

  A myA;
  UnitTestRegister::instance().register_func(&A::print, std::ref(myA));
  UnitTestRegister::instance().register_func(&A::add, std::ref(myA), 2.0);
  UnitTestRegister::instance().register_func(&A::print, std::ref(myA));

  Logger::instance();
  Hdf5Wrapper hdf;

  UnitTestRegister::instance().runUnitTests();

  return 0;
}
