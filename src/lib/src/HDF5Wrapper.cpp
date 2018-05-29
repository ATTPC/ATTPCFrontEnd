#define HDF5WRAPPER_CPP
#include <HDF5Wrapper.hpp>

#include <iostream>

namespace attpcfe {

  std::ostream& operator << (std::ostream& os, HDF5Wrapper::IO_MODE const& mode) {

    (mode == HDF5Wrapper::IO_MODE::READ) ? os << "READ": os << "WRITE";
    return os;
  }
  
  class HDF5Wrapper::HDF5WrapperImpl {

  public:
    HDF5WrapperImpl() {}
    ~HDF5WrapperImpl() {}
  };

  HDF5Wrapper::HDF5Wrapper() : _pimpl{new HDF5WrapperImpl{}, [](HDF5WrapperImpl* ptr) { delete ptr; }} {}

  std::optional<hid_t> HDF5Wrapper::OpenFile(std::string const& filename, IO_MODE mode)
  {
    hid_t fileId;
    (mode == IO_MODE::READ) ?
      fileId = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT) :
      fileId = H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

    if (fileId >= 0)
    {
      std::cout << "> HDF5Wrapper::OpenFile:MESSAGE, opening file: " << filename << " with mode: " << mode << " and ID: " << fileId << '\n';
      return {fileId};
    }
    else
    {
      std::cerr << "> HDF5Wrapper::OpenFile:ERROR, invalid ID for file: " << filename << '\n';
      return {std::nullopt};
    }
  }

  void HDF5Wrapper::CloseFile(hid_t fileId)
  {
    herr_t retId = H5Fclose(fileId);
    if (retId >= 0)
      std::cout << "> HDF5Wrapper::CloseFile:MESSAGE, closing file with ID: " << fileId << '\n';
    else
      std::cerr << "> HDF5Wrapper::CloseFile:ERROR, cannot close file with ID: " << fileId << '\n';
  }

  
}
