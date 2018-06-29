#include <data_handler.hpp>
#include <hdf5_wrapper.hpp>
#include <task_system.hpp>
#include <state.hpp>
#include <pad.hpp>
#include <raw_event.hpp>
#include <hit.hpp>
#include <hit_list.hpp>
#include <event.hpp>
#include <pattern_event.hpp>
#include <track_event.hpp>

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;
using namespace attpcfe;

void process_raw_event() {

  raw_event _raw_event;
  state::instance().pop_raw_event(_raw_event);
  
  event _event{_raw_event.id(), _raw_event.n_pads()};

  for (auto const& pad : _raw_event.pads())
  {
    hit_list _hits;

    double charge = 1.0;
    std::vector<double> pos{0., 0., 0.};
    hit _hit{std::move(pos), charge};
    _hits.add_hit(std::move(_hit));
    
    _event.add_hit_list(std::move(_hits));
  }

  std::cout << "> process_raw_event: " << _raw_event.id() << ' ' << std::this_thread::get_id() << '\n';

  state::instance().push_event(std::move(_event));
}

void process_event() {

  event _event;
  state::instance().pop_event(_event);

  pattern_event _pattern_event{_event.id()};

  std::cout << "> process_event: " << _event.id() << ' ' << std::this_thread::get_id() << '\n';
  std::this_thread::sleep_for(0.001s);

  state::instance().push_pattern_event(std::move(_pattern_event));
}

void process_pattern_event(int n)
{
  pattern_event _pattern_event;
  state::instance().pop_pattern_event(_pattern_event);

  track_event _track_event{_pattern_event.id()};

  std::cout << "> process_pattern_event: " << _pattern_event.id() << ' ' << std::this_thread::get_id() << ' ' << n << '\n';
  std::this_thread::sleep_for(0.001s);

  state::instance().push_track_event(std::move(_track_event));
}

int main(int argc, char* argv[]) {

  auto start = std::chrono::system_clock::now();

  std::vector<std::future<void>> futures;

  task_system _task_system;

  data_handler<hdf5_wrapper> _data_handler;
  _data_handler.open("/home/nico/Downloads/perico.h5");
  auto n_raw_events = _data_handler.n_raw_events();

  state::instance().reserve_stacks(n_raw_events);

  for (std::size_t i_raw_event = 0; i_raw_event < n_raw_events; ++i_raw_event)
  {
    std::cout << "> read_raw_event: " << i_raw_event << '\n';
    
    auto n_pads = _data_handler.n_pads(i_raw_event);
    raw_event _raw_event{i_raw_event, n_pads};

    for (std::size_t i_pad = 0; i_pad < n_pads; ++i_pad)
    {
      pad _pad;
      _pad.set_raw_data(_data_handler.pad_raw_data(i_pad));
      _raw_event.add_pad(std::move(_pad));
    }
    _data_handler.end_raw_event();
    
    state::instance().push_raw_event(std::move(_raw_event));

    auto f_event = _task_system.async(process_raw_event);
    auto f_pattern_event = _task_system.then(f_event, process_event);
    auto f_track_event = _task_system.then(f_pattern_event, process_pattern_event, 2);
    futures.push_back(std::move(f_track_event));
  }

  for (auto const& f : futures) f.wait();

  std::cout << "> " << state::instance().n_track_events() << " track events on stack\n";
  
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration<double>{end - start};
  std::cout << "> ATTPCFE app:MESSAGE, elapsed time: " << duration.count() << "s\n";
  
  return 0;
}
