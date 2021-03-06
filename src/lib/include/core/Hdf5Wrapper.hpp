#ifndef HDF5WRAPPER_HPP
#define HDF5WRAPPER_HPP
#ifdef UNITTEST
#include <utils/UnitTestable.hpp>
#endif

#include <hdf5.h>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>

#include <iostream>

namespace attpcfe {

#ifdef UNITTEST
  class Hdf5Wrapper : public UnitTestable<Hdf5Wrapper> {

    friend struct Test<Hdf5Wrapper>;
    static void test();
#else
  class Hdf5Wrapper {
#endif
    
    class Hdf5WrapperImpl;
    std::unique_ptr<Hdf5WrapperImpl, void(*)(Hdf5WrapperImpl*)> _pImpl;

  public:
    Hdf5Wrapper();
    Hdf5Wrapper(Hdf5Wrapper const&);
    Hdf5Wrapper& operator=(Hdf5Wrapper const&);
    Hdf5Wrapper(Hdf5Wrapper&&) noexcept = default;
    Hdf5Wrapper& operator=(Hdf5Wrapper&&) noexcept = default;

    enum class IO_MODE {
      READ,
      WRITE
    };

    std::optional<hid_t> openFile(std::string const& file, IO_MODE mode) const;
    std::tuple<std::optional<hid_t>, hsize_t> openGroup(hid_t fileId, char const* group) const;
    std::tuple<std::optional<hid_t>, std::vector<hsize_t> > openDataset(hid_t locId, char const* dataset) const;
    void closeFile(hid_t file) const;
    void closeGroup(hid_t group) const;
    void closeDataset(hid_t dataset) const;

    template<typename T>
    void readSlab(hid_t dataset, hsize_t* counts, hsize_t* offsets, hsize_t* dimsOut, T* data)
    {
      hid_t dataspace = H5Dget_space(dataset);
      H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offsets, nullptr, counts, nullptr);
      hid_t memspace = H5Screate_simple(2, dimsOut, nullptr);
      if constexpr (std::is_same_v<T, int16_t>) H5Dread(dataset, H5T_NATIVE_INT16, memspace, dataspace, H5P_DEFAULT, data);
      else if constexpr (std::is_same_v<T, double>) H5Dread(dataset, H5T_NATIVE_DOUBLE, memspace, dataspace, H5P_DEFAULT, data);
      H5Sclose(memspace);
      H5Sclose(dataspace);
    }

    // Following methods satisfy the DataHandler interface
    std::tuple<std::size_t, std::size_t> open(std::string const& file);
    std::size_t nPads(std::size_t iRawEvent);
    std::vector<int16_t> padRawData(std::size_t iPad);
    void endRawEvent() const;
    void close() const;
  };
}
#endif
