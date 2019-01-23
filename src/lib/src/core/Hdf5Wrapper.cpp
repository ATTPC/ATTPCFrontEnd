#define HDF5WRAPPER_CPP
#include <core/Hdf5Wrapper.hpp>
#include <iostream>
#include <algorithm>

#ifdef UNITTEST
#include <utils/Logger.hpp>
#include <cassert>
#endif

/*
  Wrapper around specific h5 file format.
  Data structure:
  > group: "get"
  > .. dataset: "i" (i = event number)

  Dataset are n x 517 int16 arrays, n = number of pads in event.
  First 5 entries are reserved for addressing, next 512 entries are raw ADCs.
*/

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

  std::optional<hid_t> Hdf5Wrapper::openFile(std::string const& file, IO_MODE mode)
  {
    hid_t fileId;
    (mode == IO_MODE::READ) ?
      fileId = H5Fopen(file.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT) :
      fileId = H5Fopen(file.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

    if (fileId >= 0)
    {
      return {fileId};
    }
    else
    {
      std::cerr << "> Hdf5Wrapper::openFile:ERROR, invalid ID for file: " << file << '\n';
      return {std::nullopt};
    }
  }

  std::tuple<std::optional<hid_t>, hsize_t> Hdf5Wrapper::openGroup(hid_t fileId, char const* group)
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
      std::cerr << "> Hdf5Wrapper::openGroup:ERROR, invalid ID for group: " << group << '\n';
      return {std::nullopt, 0};
    }
  }

  std::tuple<std::optional<hid_t>, std::vector<hsize_t> > Hdf5Wrapper::openDataset(hid_t locId, char const* dataset)
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
      std::cerr << "> Hdf5Wrapper::openDataset:ERROR, invalid ID for dataset: " << dataset << '\n';
      return {std::nullopt, {}};
    }
  }

  void Hdf5Wrapper::closeFile(hid_t fileId) const
  {
    herr_t retId = H5Fclose(fileId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::closeFile:ERROR, cannot close file with ID: " << fileId << '\n';
  }

  void Hdf5Wrapper::closeGroup(hid_t groupId) const
  {
    herr_t retId = H5Gclose(groupId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::closeGroup:ERROR, cannot close group with ID: " << groupId << '\n';
  }

  void Hdf5Wrapper::closeDataset(hid_t datasetId) const
  {
    herr_t retId = H5Dclose(datasetId);
    if (retId < 0)
      std::cerr << "> Hdf5Wrapper::closeDataset:ERROR, cannot close dataset with ID: " << datasetId << '\n';
  }

  std::tuple<std::size_t, std::size_t> Hdf5Wrapper::open(std::string const& file)
  {
    auto f = openFile(file, Hdf5Wrapper::IO_MODE::READ);
    if (!f.has_value()) return {0, 0};
    _pImpl->_file = f.value();
    auto [group, nEntries] = openGroup(f.value(), "get");
    if (!group.has_value()) return {0, 0};
    _pImpl->_group = group.value();

    auto events = std::vector<int>{}; events.reserve(nEntries);
    for (std::size_t iEntry = 0; iEntry < nEntries; ++iEntry)
    {
      auto nameLength = std::size_t{10};
      char name[nameLength];
      if (H5Gget_objname_by_idx(group.value(), iEntry, name, nameLength) > 0)
      {
      	events.push_back(std::atoi(name));
      }
    }

    auto fEvent = static_cast<std::size_t>(*std::min_element(std::begin(events), std::end(events)));
    return {nEntries, fEvent};
  }

  std::size_t Hdf5Wrapper::nPads(std::size_t iRawEvent)
  {
    std::string datasetName = std::to_string(iRawEvent);
    auto [dataset, dims] = openDataset(_pImpl->_group, datasetName.c_str());
    if (!dataset.has_value()) return 0;
    _pImpl->_dataset = dataset.value();
    return dims[0];
  }

  std::vector<int16_t> Hdf5Wrapper::padRawData(std::size_t iPad)
  {
    int16_t data[517];
    hsize_t counts[2] = {1, 517};
    hsize_t offsets[2] = {iPad, 0};
    hsize_t dimsOut[2] = {1, 517};
    readSlab<int16_t>(_pImpl->_dataset, counts, offsets, dimsOut, data);
    return {data, data + 517};
  }

  void Hdf5Wrapper::endRawEvent() const
  {
    closeDataset(_pImpl->_dataset);
  }

  void Hdf5Wrapper::close() const
  {
    closeGroup(_pImpl->_group);
    closeFile(_pImpl->_file);
  }

#ifdef UNITTEST
  void Hdf5Wrapper::test()
  {
    Hdf5Wrapper hdf;
    auto file = hdf.openFile("/home/nico/Desktop/perico.h5", Hdf5Wrapper::IO_MODE::READ);
    assert(file.has_value());

    gLogDebug << "Opened data file";

    auto [group, n_entries] = hdf.openGroup(file.value(), "get");
    assert(group.has_value());

    gLogDebug << "Opened data group";
  
    auto [dataset, dims] = hdf.openDataset(group.value(), "0");
    assert(dataset.has_value());

    gLogDebug << "Opened data set";

    hdf.closeDataset(dataset.value());
    hdf.closeGroup(group.value());
    hdf.closeFile(file.value());

    gLogDebug << "Closed all";
  }
#endif  
}
