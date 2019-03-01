#ifndef UNITTESTREGISTER_INL
#define UNITTESTREGISTER_INL

namespace attpcfe {

  template<typename T, typename F, typename... Args>
  void UnitTestRegister::registerTest(T const& name, F&& func, Args&&... args) 
  {
    auto unitTest = [_func = std::forward<F>(func),
		     _args = std::make_tuple(std::forward<Args>(args)...)]() 
      {
	std::apply(_func, _args);
      };
    
    registerUnitTest(name, std::move(unitTest));
  }
}
#endif
