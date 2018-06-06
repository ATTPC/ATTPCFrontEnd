#include <hdf5_wrapper.hpp>
#include <cassert>

using namespace attpcfe;

int main() {

  hdf5_wrapper h;
  auto fileId = h.open_file("/home/nico/Downloads/test.h5", hdf5_wrapper::IO_MODE::READ);
  assert(fileId.has_value());

  auto groupId = h.open_group(fileId.value(), "get");
  assert(groupId.has_value());
  
  auto datasetId = h.open_dataset(groupId.value(), "0");
  assert(datasetId.has_value());

  h.close_dataset(datasetId.value());
  h.close_group(groupId.value());
  h.close_file(fileId.value());
  
  return 0;
}
