#define HDF5WRAPPER_CPP
#include <core/Hdf5Wrapper.hpp>

#include <iostream>

namespace attpcfe {

  std::ostream& operator << (std::ostream& os, Hdf5Wrapper::IO_MODE const& mode) {

    (mode == Hdf5Wrapper::IO_MODE::READ) ? os << "READ": os << "WRITE";
    return os;
  }
  
  class Hdf5Wrapper::Hdf5WrapperImpl {

  public:
    Hdf5WrapperImpl() {}
    ~Hdf5WrapperImpl() {}

    hid_t _file;
    hid_t _group;
    hid_t _dataset;
  };

  Hdf5Wrapper::Hdf5Wrapper() : _pImpl{new Hdf5WrapperImpl{}, [](Hdf5WrapperImpl* ptr) { delete ptr; }} {}

  std::optional<hid_t> Hdf5Wrapper::OpenFile(char const* file, IO_MODE mode)
  {
    hid_t fileId;
    (mode == IO_MODE::READ) ?
      fileId = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT) :
      fileId = H5Fopen(file, H5F_ACC_RDWR, H5P_DEFAULT);

    if (fileId >= 0)
    {
      return {fileId};
    }
    else
    {
      std::cerr << "> Hdf5Wrapper::OpenFile:ERROR, invalid ID for file: " << file << '\n';
      return {std::nullopt};
    }
  }

  std::tuple<std::optional<hid_t>, hsize_t> Hdf5Wrapper::OpenGroup(hid_t fileId, char const* group)
  {
    hid_t groupId = H5Gopen2(fileId, group, H5P_DEFAULT);
    if (groupId >= 0)
    {
      hsize_t size;
      H5Gget_num_objs(groupId, &size);
      return {groupId, size};
    }
    else
    {
      std::cerr << "> Hdf5Wrapper::OpenGroup:ERROR, invalid ID for group: " << group << '\n';
      return {std::nullopt, 0};
    }
  }

  std::tuple<std::optional<hid_t>, std::vector<hsize_t> > Hdf5Wrapper::OpenDataset(hid_t locId, char const* dataset)
  {
    hid_t datasetId = H5Dopen2(locId, dataset, H5P_DEFAULT);
    if (datasetId >= 0)
    {
      hid_t dspaceId = H5Dget_space(datasetId);
      int n_dims = H5Sget_simple_extent_ndims(dspaceId);
      hsize_t dims[n_dims];
      H5Sget_simple_extent_dims(dspaceId, dims, nullptr);
      return {datasetId, {dims, dims + n_dims}};
    }
    else
    {
      std::cerr << "> Hdf5Wrapper::OpenDataset:ERROR, invalid ID for dataset: " << dataset << '\n';
      return {std::nullopt, {}};
    }
  }

  void Hdf5Wrapper::CloseFile(hid_t fileId)
  {
    herr_t retId = H5Fclose(fileId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::CloseFile:ERROR, cannot close file with ID: " << fileId << '\n';
  }

  void Hdf5Wrapper::CloseGroup(hid_t groupId)
  {
    herr_t retId = H5Gclose(groupId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::CloseGroup:ERROR, cannot close group with ID: " << groupId << '\n';
  }

  void Hdf5Wrapper::CloseDataset(hid_t datasetId)
  {
    herr_t retId = H5Dclose(datasetId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::CloseDataset:ERROR, cannot close dataset with ID: " << datasetId << '\n';
  }

  std::size_t Hdf5Wrapper::Open(char const* file)
  {
    auto f = OpenFile(file, Hdf5Wrapper::IO_MODE::READ);
    if (!f.has_value()) return 0;
    _pImpl->_file = f.value();
    auto [group, n_entries] = OpenGroup(f.value(), "get");
    if (!group.has_value()) return 0;
    _pImpl->_group = group.value();
    return n_entries;
  }

  std::size_t Hdf5Wrapper::NPads(std::size_t iRawEvent)
  {
    std::string datasetName = std::to_string(iRawEvent);
    auto [dataset, dims] = OpenDataset(_pImpl->_group, datasetName.c_str());
    if (!dataset.has_value()) return 0;
    _pImpl->_dataset = dataset.value();
    return dims[0];
  }

  std::vector<int16_t> Hdf5Wrapper::PadRawData(std::size_t iPad)
  {
    int16_t data[517];
    hsize_t counts[2] = {1, 517};
    hsize_t offsets[2] = {iPad, 0};
    hsize_t dimsOut[2] = {1, 517};
    ReadSlab<int16_t>(_pImpl->_dataset, counts, offsets, dimsOut, data);
    return {data, data + 517};
  }

  void Hdf5Wrapper::EndRawEvent()
  {
    CloseDataset(_pImpl->_dataset);
  }

  void Hdf5Wrapper::Close()
  {
    CloseGroup(_pImpl->_group);
    CloseFile(_pImpl->_file);
  }
}
