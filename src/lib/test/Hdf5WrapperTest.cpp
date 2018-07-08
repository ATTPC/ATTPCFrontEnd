#include <core/Hdf5Wrapper.hpp>
#include <cassert>

using namespace attpcfe;

int main() {

  Hdf5Wrapper hdf;
  auto file = hdf.openFile("/home/nico/Downloads/test.h5", Hdf5Wrapper::IO_MODE::READ);
  assert(file.has_value());

  auto [group, n_entries] = hdf.openGroup(file.value(), "get");
  assert(group.has_value());
  
  auto [dataset, dims] = hdf.openDataset(group.value(), "0");
  assert(dataset.has_value());

  hdf.closeDataset(dataset.value());
  hdf.closeGroup(group.value());
  hdf.closeFile(file.value());
  
  return 0;
}
