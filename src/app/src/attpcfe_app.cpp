#include <data_handler.hpp>
#include <hdf5_wrapper.hpp>
#include <task_system.hpp>
#include <state.hpp>
#include <raw_event.hpp>
#include <pad.hpp>

#include <chrono>
#include <iostream>

using namespace attpcfe;

void print_raw_event() {

  raw_event _raw_event;
  state::instance().pop_raw_event(_raw_event);
  std::cout << _raw_event.n_pads() << '\n';
}

int main(int argc, char* argv[]) {

  auto start = std::chrono::system_clock::now();

  task_system _task_system;

  data_handler<hdf5_wrapper> _data_handler;
  _data_handler.open("/home/nico/Downloads/perico.h5");
  auto n_raw_events = _data_handler.n_raw_events();

  state::instance().reserve_stacks(n_raw_events);

  for (std::size_t i_raw_event = 0; i_raw_event < n_raw_events; ++i_raw_event)
  {
    auto n_pads = _data_handler.n_pads(i_raw_event);
    raw_event _raw_event{n_pads};

    for (std::size_t i_pad = 0; i_pad < n_pads; ++i_pad)
    {
      pad _pad;
      _pad.set_raw_data(_data_handler.pad_raw_data(i_pad));
      _raw_event.add_pad(std::move(_pad));
    }

    state::instance().push_raw_event(std::move(_raw_event));
    _task_system.void_async(print_raw_event);
    _data_handler.end_raw_event();
  }

  _data_handler.close();
  
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration<double>{end - start};
  std::cout << "> ATTPCFE app:MESSAGE, elapsed time: " << duration.count() << "s\n";
  
  return 0;
}
