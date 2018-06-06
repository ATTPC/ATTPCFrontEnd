#define HDF5_WRAPPER_CPP
#include <hdf5_wrapper.hpp>

#include <iostream>

namespace attpcfe {

  std::ostream& operator << (std::ostream& os, hdf5_wrapper::IO_MODE const& mode) {

    (mode == hdf5_wrapper::IO_MODE::READ) ? os << "READ": os << "WRITE";
    return os;
  }
  
  class hdf5_wrapper::hdf5_wrapper_impl {

  public:
    hdf5_wrapper_impl() {}
    ~hdf5_wrapper_impl() {}
  };

  hdf5_wrapper::hdf5_wrapper() : _pimpl{new hdf5_wrapper_impl{}, [](hdf5_wrapper_impl* ptr) { delete ptr; }} {}

  std::optional<hid_t> hdf5_wrapper::open_file(char const* file, IO_MODE mode)
  {
    hid_t fileId;
    (mode == IO_MODE::READ) ?
      fileId = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT) :
      fileId = H5Fopen(file, H5F_ACC_RDWR, H5P_DEFAULT);

    if (fileId >= 0)
    {
      std::cout << "> hdf5_wrapper::open_file:MESSAGE, opening file: " << file << ", mode: " << mode << ", ID: " << fileId << '\n';
      return {fileId};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_file:ERROR, invalid ID for file: " << file << '\n';
      return {std::nullopt};
    }
  }

  std::optional<hid_t> hdf5_wrapper::open_group(hid_t fileId, char const* group)
  {
    hid_t groupId = H5Gopen2(fileId, group, H5P_DEFAULT);
    if (groupId >= 0)
    {
      std::cout << "> hdf5_wrapper::open_group:MESSAGE, opening group: " << group << ", ID: " << groupId << '\n';
      return {groupId};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_group:ERROR, invalid ID for group: " << group << '\n';
      return {std::nullopt};
    }
  }

  std::optional<hid_t> hdf5_wrapper::open_dataset(hid_t locId, char const* dataset)
  {
    hid_t datasetId = H5Dopen2(locId, dataset, H5P_DEFAULT);
    if (datasetId >= 0)
    {
      std::cout << "> hdf5_wrapper::open_dataset:MESSAGE, opening dataset: " << dataset << ", ID: " << datasetId << '\n';
      return {datasetId};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_dataset:ERROR, invalid ID for dataset: " << dataset << '\n';
      return {std::nullopt};
    }
  }

  void hdf5_wrapper::close_file(hid_t fileId)
  {
    herr_t retId = H5Fclose(fileId);
    if (retId < 0)
      std::cerr << "> hdf5_wrapper::close_file:ERROR, cannot close file with ID: " << fileId << '\n';
  }

  void hdf5_wrapper::close_group(hid_t groupId)
  {
    herr_t retId = H5Gclose(groupId);
    if (retId < 0)
      std::cerr << "> hdf5_wrapper::close_group:ERROR, cannot close group with ID: " << groupId << '\n';
  }

  void hdf5_wrapper::close_dataset(hid_t datasetId)
  {
    herr_t retId = H5Dclose(datasetId);
    if (retId < 0)
      std::cerr << "> hdf5_wrapper::close_dataset:ERROR, cannot close dataset with ID: " << datasetId << '\n';
  }

  
}
