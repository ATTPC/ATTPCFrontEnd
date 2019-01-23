#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#include <memory>

namespace attpcfe {

  class UnitTest {

    struct concept_t {

      virtual ~concept_t() = default;
      virtual void test_() const = 0;
    };

    template <typename T>
    struct model_t final : public concept_t {
      
      model_t(T data);

      void test_() const override;

      T _data;
    };
    
    std::shared_ptr<concept_t const> _self;

  public:
    template<typename T>
    UnitTest(T impl);
    
    friend void test(UnitTest const& unitTest);
  };
}
#include <utils/UnitTest.inl>
#endif
