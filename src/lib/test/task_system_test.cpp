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

  for (int i = 0; i < 100; ++i)
  {
    auto f = ts.async([i, &sum]()
		      {
			sum += i;
			std::cout << i << '\n';
			return i;
		      });
    futures.push_back(std::move(f));
  }

  assert(futures[42].get() == 42);

  //for (auto& f :  futures)
  //{
  //  std::cout << f.get() << '\n';
  //}
  
  return 0;
}
