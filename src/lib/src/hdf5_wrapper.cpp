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

    hid_t _file;
    hid_t _group;
    hid_t _dataset;
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
      //std::cout << "> hdf5_wrapper::open_file:MESSAGE, opening file: " << file << ", mode: " << mode << ", ID: " << fileId << '\n';
      return {fileId};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_file:ERROR, invalid ID for file: " << file << '\n';
      return {std::nullopt};
    }
  }

  std::tuple<std::optional<hid_t>, hsize_t> hdf5_wrapper::open_group(hid_t fileId, char const* group)
  {
    hid_t groupId = H5Gopen2(fileId, group, H5P_DEFAULT);
    if (groupId >= 0)
    {
      //std::cout << "> hdf5_wrapper::open_group:MESSAGE, opening group: " << group << ", ID: " << groupId << '\n';
      hsize_t size;
      H5Gget_num_objs(groupId, &size);
      return {groupId, size};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_group:ERROR, invalid ID for group: " << group << '\n';
      return {std::nullopt, 0};
    }
  }

  std::tuple<std::optional<hid_t>, std::vector<hsize_t> > hdf5_wrapper::open_dataset(hid_t locId, char const* dataset)
  {
    hid_t datasetId = H5Dopen2(locId, dataset, H5P_DEFAULT);
    if (datasetId >= 0)
    {
      //std::cout << "> hdf5_wrapper::open_dataset:MESSAGE, opening dataset: " << dataset << ", ID: " << datasetId << '\n';
      hid_t dspaceId = H5Dget_space(datasetId);
      int n_dims = H5Sget_simple_extent_ndims(dspaceId);
      hsize_t dims[n_dims];
      H5Sget_simple_extent_dims(dspaceId, dims, nullptr);
      return {datasetId, {dims, dims + n_dims}};
    }
    else
    {
      std::cerr << "> hdf5_wrapper::open_dataset:ERROR, invalid ID for dataset: " << dataset << '\n';
      return {std::nullopt, {}};
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

  std::size_t hdf5_wrapper::open(char const* file)
  {
    auto f = open_file(file, hdf5_wrapper::IO_MODE::READ);
    if (!f.has_value()) return 0;
    _pimpl->_file = f.value();
    auto [group, n_entries] = open_group(f.value(), "get");
    if (!group.has_value()) return 0;
    _pimpl->_group = group.value();
    return n_entries;
  }

  std::size_t hdf5_wrapper::n_pads(std::size_t i_raw_event)
  {
    std::string dataset_name = std::to_string(i_raw_event);
    auto [dataset, dims] = open_dataset(_pimpl->_group, dataset_name.c_str());
    if (!dataset.has_value()) return 0;
    _pimpl->_dataset = dataset.value();
    return dims[0];
  }

  std::vector<int16_t> hdf5_wrapper::pad_raw_data(std::size_t i_pad)
  {
    int16_t data[517];
    hsize_t counts[2] = {1, 517};
    hsize_t offsets[2] = {i_pad, 0};
    hsize_t dims_out[2] = {1, 517};
    read_slab<int16_t>(_pimpl->_dataset, counts, offsets, dims_out, data);
    return {data, data + 517};
  }

  void hdf5_wrapper::end_raw_event()
  {
    close_dataset(_pimpl->_dataset);
  }

  void hdf5_wrapper::close()
  {
    close_group(_pimpl->_group);
    close_file(_pimpl->_file);
  }
}
