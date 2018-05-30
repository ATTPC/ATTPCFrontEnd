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

  std::optional<hid_t> HDF5Wrapper::OpenFile(char const* file, IO_MODE mode)
  {
    hid_t fileId;
    (mode == IO_MODE::READ) ?
      fileId = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT) :
      fileId = H5Fopen(file, H5F_ACC_RDWR, H5P_DEFAULT);

    if (fileId >= 0)
    {
      std::cout << "> HDF5Wrapper::OpenFile:MESSAGE, opening file: " << file << ", mode: " << mode << ", ID: " << fileId << '\n';
      return {fileId};
    }
    else
    {
      std::cerr << "> HDF5Wrapper::OpenFile:ERROR, invalid ID for file: " << file << '\n';
      return {std::nullopt};
    }
  }

  std::optional<hid_t> HDF5Wrapper::OpenGroup(hid_t fileId, char const* group)
  {
    hid_t groupId = H5Gopen2(fileId, group, H5P_DEFAULT);
    if (groupId >= 0)
    {
      std::cout << "> HDF5Wrapper::OpenGroup:MESSAGE, opening group: " << group << ", ID: " << groupId << '\n';
      return {groupId};
    }
    else
    {
      std::cerr << "> HDF5Wrapper::OpenGroup:ERROR, invalid ID for group: " << group << '\n';
      return {std::nullopt};
    }
  }

  std::optional<hid_t> HDF5Wrapper::OpenDataset(hid_t locId, char const* dataset)
  {
    hid_t datasetId = H5Dopen2(locId, dataset, H5P_DEFAULT);
    if (datasetId >= 0)
    {
      std::cout << "> HDF5Wrapper::OpenDataset:MESSAGE, opening dataset: " << dataset << ", ID: " << datasetId << '\n';
      return {datasetId};
    }
    else
    {
      std::cerr << "> HDF5Wrapper::OpenDataset:ERROR, invalid ID for dataset: " << dataset << '\n';
      return {std::nullopt};
    }
  }

  void HDF5Wrapper::CloseFile(hid_t fileId)
  {
    herr_t retId = H5Fclose(fileId);
    if (retId < 0)
      std::cerr << "> HDF5Wrapper::CloseFile:ERROR, cannot close file with ID: " << fileId << '\n';
  }

  void HDF5Wrapper::CloseGroup(hid_t groupId)
  {
    herr_t retId = H5Gclose(groupId);
    if (retId < 0)
      std::cerr << "> HDF5Wrapper::CloseGroup:ERROR, cannot close group with ID: " << groupId << '\n';
  }

  void HDF5Wrapper::CloseDataset(hid_t datasetId)
  {
    herr_t retId = H5Dclose(datasetId);
    if (retId < 0)
      std::cerr << "> HDF5Wrapper::CloseGroup:ERROR, cannot close dataset with ID: " << datasetId << '\n';
  }

  
}
