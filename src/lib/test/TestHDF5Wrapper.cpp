#include <HDF5Wrapper.hpp>

using namespace attpcfe;

int main() {

  HDF5Wrapper HDF5;
  auto fileId = HDF5.OpenFile("/home/nico/Downloads/test.h5", HDF5Wrapper::IO_MODE::READ);
  if (!fileId.has_value()) return -1;

  HDF5.CloseFile(fileId.value());
  
  return 0;
}
