#include <task_system.hpp>
#include <atomic>
#include <vector>
#include <future>
#include <iostream>
#include <cassert>
#include <chrono>
using namespace std::chrono_literals;
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
			std::this_thread::sleep_for(0.5s);
			std::cout << i << '\n';
			return i;
		      });
    futures.push_back(std::move(f));
  }

  assert(futures[32].get() == 32);

  //for (auto& f :  futures)
  //{
  //  std::cout << f.get() << '\n';
  //}
  
  return 0;
}
