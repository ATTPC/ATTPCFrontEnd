#ifndef HDF5_WRAPPER_HPP
#define HDF5_WRAPPER_HPP

#include <hdf5.h>

#include <memory>
#include <optional>
#include <tuple>
#include <vector>

#include <iostream>

namespace attpcfe {

  class hdf5_wrapper {

    class hdf5_wrapper_impl;
    std::unique_ptr<hdf5_wrapper_impl, void(*)(hdf5_wrapper_impl*)> _pimpl;

  public:
    hdf5_wrapper();
    hdf5_wrapper(hdf5_wrapper const&) = delete;
    hdf5_wrapper& operator=(hdf5_wrapper const&) = delete;

    enum class IO_MODE {
      READ,
      WRITE
    };
    std::optional<hid_t> open_file(char const* file, IO_MODE mode);
    std::tuple<std::optional<hid_t>, hsize_t> open_group(hid_t fileId, char const* group);
    std::tuple<std::optional<hid_t>, std::vector<hsize_t> > open_dataset(hid_t locId, char const* dataset);
    void close_file(hid_t file);
    void close_group(hid_t group);
    void close_dataset(hid_t dataset);

    template<typename T>
    void read_slab(hid_t dataset, hsize_t* counts, hsize_t* offsets, hsize_t* dims_out, T* data)
    {
      hid_t dataspace = H5Dget_space(dataset);
      H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offsets, nullptr, counts, nullptr);
      hid_t memspace = H5Screate_simple(2, dims_out, nullptr);
      H5Dread(dataset, H5T_NATIVE_INT16, memspace, dataspace, H5P_DEFAULT, data);
      H5Sclose(memspace);
      H5Sclose(dataspace);
    }

    // Following methods satisfy the data_handler interface
    std::size_t open(char const* file);
    std::size_t n_pads(std::size_t i_raw_event);
    std::vector<int16_t> pad_raw_data(std::size_t i_pad);
    void end_raw_event();
    void close();
  };
}

#endif
