#include <task_system.hpp>
#include <atomic>
#include <vector>
#include <future>
#include <iostream>
#include <cassert>

using namespace attpcfe;

int main() {

  std::atomic<int> sum{0};
  task_system ts;
  std::vector<std::future<int> > futures;

  try {
  for (int i = 0; i < 60000; ++i)
  {
    auto f = ts.async([i, &sum]()
		      {
			sum += i;
			return i;
		      });
    futures.push_back(std::move(f));
  }
  }
  catch (const std::future_error& e) {
    std::cout << "Caught a future_error with code \"" << e.code()
	      << "\"\nMessage: \"" << e.what() << "\"\n";
  }

  for (auto& f :  futures)
  {
    std::cout << f.get() << '\n';
  }
  
  return 0;
}
