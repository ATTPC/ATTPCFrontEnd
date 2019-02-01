#ifndef UNITTESTREGISTER_INL
#define UNITTESTREGISTER_INL

namespace attpcfe {

  template<typename F, typename... Args>
  void UnitTestRegister::register_func(F&& func, Args&&... args) 
  {
    auto unitTest = [_func = std::forward<F>(func),
		     _args = std::make_tuple(std::forward<Args>(args)...)]() 
      {
	std::apply(_func, _args);
      };
    
    register_(std::move(unitTest));
  }
  
  /*
  template <typename Base, typename F, typename I, typename... Args>
  void UnitTestRegister::register_func(F Base::* func, I&& instance, Args&&... args)
  {
    if constexpr (std::is_member_function_pointer_v<decltype(func)>) // Checks if non-static member function pointer.
      {
	if constexpr (std::is_base_of_v<Base, std::decay_t<I>>)
	  {
	    auto unitTest = [_instance = std::forward<I>(instance), _func = std::forward<I>(instance).*func,
			     _args = std::make_tuple(std::forward<Args>(args)...)]
	      {
		std::apply(_instance.*_func, _args);
	      };
	    register_(std::move(unitTest));
	  }
      }
  }
  */
}
#endif
