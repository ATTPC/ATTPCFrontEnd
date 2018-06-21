#include <hdf5_wrapper.hpp>
#include <cassert>

using namespace attpcfe;

int main() {

  hdf5_wrapper hdf;
  auto file = hdf.open_file("/home/nico/Downloads/test.h5", hdf5_wrapper::IO_MODE::READ);
  assert(file.has_value());

  auto [group, n_entries] = hdf.open_group(file.value(), "get");
  assert(group.has_value());
  
  auto [dataset, dims] = hdf.open_dataset(group.value(), "0");
  assert(dataset.has_value());

  hdf.close_dataset(dataset.value());
  hdf.close_group(group.value());
  hdf.close_file(file.value());
  
  return 0;
}
