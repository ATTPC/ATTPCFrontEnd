#include <HDF5Wrapper.hpp>
#include <cassert>

using namespace attpcfe;

int main() {

  HDF5Wrapper HDF5;
  auto fileId = HDF5.OpenFile("/home/nico/Downloads/test.h5", HDF5Wrapper::IO_MODE::READ);
  assert(fileId.has_value());

  auto groupId = HDF5.OpenGroup(fileId.value(), "get");
  assert(groupId.has_value());
  
  auto datasetId = HDF5.OpenDataset(groupId.value(), "0");
  assert(datasetId.has_value());

  HDF5.CloseDataset(datasetId.value());
  HDF5.CloseGroup(groupId.value());
  HDF5.CloseFile(fileId.value());
  
  return 0;
}
