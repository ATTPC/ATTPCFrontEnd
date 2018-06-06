#ifndef HDF5_WRAPPER_HPP
#define HDF5_WRAPPER_HPP

#include <hdf5.h>
#include <memory>
#include <optional>

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
    std::optional<hid_t> open_group(hid_t fileId, char const* group);
    std::optional<hid_t> open_dataset(hid_t locId, char const* dataset);
    void close_file(hid_t fileId);
    void close_group(hid_t groupId);
    void close_dataset(hid_t datasetId);
  };
}

#endif
