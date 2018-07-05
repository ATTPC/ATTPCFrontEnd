#include <core/Hdf5Wrapper.hpp>
#include <cassert>

using namespace attpcfe;

int main() {

  Hdf5Wrapper hdf;
  auto file = hdf.OpenFile("/home/nico/Downloads/test.h5", Hdf5Wrapper::IO_MODE::READ);
  assert(file.has_value());

  auto [group, n_entries] = hdf.OpenGroup(file.value(), "get");
  assert(group.has_value());
  
  auto [dataset, dims] = hdf.OpenDataset(group.value(), "0");
  assert(dataset.has_value());

  hdf.CloseDataset(dataset.value());
  hdf.CloseGroup(group.value());
  hdf.CloseFile(file.value());
  
  return 0;
}
