#ifndef HDF5WRAPPER_HPP
#define HDF5WRAPPER_HPP

#include <hdf5.h>
#include <memory>
#include <optional>

namespace attpcfe {

  class HDF5Wrapper {

  private:
    class HDF5WrapperImpl;
    std::unique_ptr<HDF5WrapperImpl, void(*)(HDF5WrapperImpl*)> _pimpl;

  public:
    HDF5Wrapper();
    HDF5Wrapper(HDF5Wrapper const&) = delete;
    HDF5Wrapper& operator=(HDF5Wrapper const&) = delete;

    enum class IO_MODE {
      READ,
      WRITE
    };
    std::optional<hid_t> OpenFile(std::string const& filename, IO_MODE mode);
    void CloseFile(hid_t fileId);
  };
}

#endif
