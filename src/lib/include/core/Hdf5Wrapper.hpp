#ifndef HDF5WRAPPER_HPP
#define HDF5WRAPPER_HPP

#include <hdf5.h>

#include <memory>
#include <optional>
#include <tuple>
#include <vector>

#include <iostream>

namespace attpcfe {

  class Hdf5Wrapper {

    class Hdf5WrapperImpl;
    std::unique_ptr<Hdf5WrapperImpl, void(*)(Hdf5WrapperImpl*)> _pImpl;

  public:
    Hdf5Wrapper();
    Hdf5Wrapper(Hdf5Wrapper const&) = delete;
    Hdf5Wrapper& operator=(Hdf5Wrapper const&) = delete;

    enum class IO_MODE {
      READ,
      WRITE
    };
    std::optional<hid_t> OpenFile(char const* file, IO_MODE mode);
    std::tuple<std::optional<hid_t>, hsize_t> OpenGroup(hid_t fileId, char const* group);
    std::tuple<std::optional<hid_t>, std::vector<hsize_t> > OpenDataset(hid_t locId, char const* dataset);
    void CloseFile(hid_t file);
    void CloseGroup(hid_t group);
    void CloseDataset(hid_t dataset);

    template<typename T>
    void ReadSlab(hid_t dataset, hsize_t* counts, hsize_t* offsets, hsize_t* dimsOut, T* data)
    {
      hid_t dataspace = H5Dget_space(dataset);
      H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offsets, nullptr, counts, nullptr);
      hid_t memspace = H5Screate_simple(2, dimsOut, nullptr);
      H5Dread(dataset, H5T_NATIVE_INT16, memspace, dataspace, H5P_DEFAULT, data);
      H5Sclose(memspace);
      H5Sclose(dataspace);
    }

    // Following methods satisfy the DataHandler interface
    std::size_t Open(char const* file);
    std::size_t NPads(std::size_t iRawEvent);
    std::vector<int16_t> PadRawData(std::size_t iPad);
    void EndRawEvent();
    void Close();
  };
}

#endif
