#ifndef UNITTEST_INL
#define UNITTEST_INL

namespace attpcfe {

  // Here declare all non-friend non-member test functions
  template <typename T>
  void test(T const& unitTest) {

    unitTest();
  }

  // model_t
  template <typename T>
  UnitTest::model_t<T>::model_t(T data) : _data{std::move(data)} {}
  
  template <typename T>
  void UnitTest::model_t<T>::test_() const {

    test(_data);
  }

  // wrapper
  template <typename T>
  UnitTest::UnitTest(T impl) : _self(std::make_shared<model_t<T>>(std::move(impl))) {}
}
#endif
