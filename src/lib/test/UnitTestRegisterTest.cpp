#include <utils/UnitTestRegister.hpp>
#include <utils/UnitTestable.hpp>
#include <iostream>

using namespace attpcfe;

// lambda
auto closure = [=](int val){ std::cout << "closure print: " << val << '\n'; };

// free function
void print(int val) { std::cout << "function print: " << val << '\n'; }

// member function from non-unit testable class
class Foo {

  int _val{0};
  
public:
  void print() const { std::cout << "Foo::print: " << _val << '\n'; }
  void add(int n) { _val += n; }
};

// unit test from unit testable class
class Bar : public UnitTestable<Bar> {

  friend struct Test<Bar>;
  static void test()
  {
    Bar b;
    b.print();
    b.add(2);
    b.print();
  }
  
  int _val{0};
  
public:
  void print() const { std::cout << "Bar::print: " << _val << '\n'; }
  void add(int n) { _val += n; }
};
REGISTER_TYPE_NAME(Bar, class Bar);

int main() {

  // register tests for non-unit testable objects
  UnitTestRegister::instance().registerTest("closure", closure, 2);
  UnitTestRegister::instance().registerTest("free function", print, 2);
  Foo foo;
  UnitTestRegister::instance().registerTest("class Foo", &Foo::print, std::ref(foo));
  UnitTestRegister::instance().registerTest("class Foo", &Foo::add, std::ref(foo), 2);
  UnitTestRegister::instance().registerTest("class Foo", &Foo::print, std::ref(foo));

  // auto register unit testable object
  Bar bar;

  // run all unit tests
  UnitTestRegister::instance().runRegister();
  
  return 0;
}
