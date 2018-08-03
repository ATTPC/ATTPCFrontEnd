#define RECONSTRUCTIONTASKS_CPP
#include <gui/ReconstructionDockTasks.hpp>
#include <gui/ReconstructionDockState.hpp>
#include <core/TaskSystem.hpp>
#include <core/ReconstructionState.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>
#include <core/DataHandler.hpp>
#include <core/Hdf5Wrapper.hpp>
#include <core/Pad.hpp>
#include <core/RawEvent.hpp>
#include <reco/PSATask.hpp>

namespace attpcfe {

  class ReconstructionTask::ReconstructionTaskImpl {

  public:
    ReconstructionTaskImpl(std::string file, std::size_t fromEvent, std::size_t nEvents, ReconstructionDockState* state) :
      _rawDataFile{std::move(file)}, _fromEvent{fromEvent}, _nEvents{nEvents}, _pState{state} {}

    std::string _rawDataFile;
    std::size_t _fromEvent;
    std::size_t _nEvents;
    ReconstructionDockState* _pState;
  };

  ReconstructionTask::ReconstructionTask(std::string file, std::size_t fromEvent, std::size_t nEvents, ReconstructionDockState* state) :
    _pImpl{new ReconstructionTaskImpl{std::move(file), fromEvent, nEvents, state}, [](ReconstructionTaskImpl* ptr){ delete ptr; }} {}
  
  void ReconstructionTask::run()
  {
    // Create task system
    TaskSystem taskSystem;
    std::vector<std::future<void>> futures;
    
    // Open input file with data handler
    DataHandler<Hdf5Wrapper> dataHandler;
    dataHandler.open(_pImpl->_rawDataFile.c_str());
    auto nRawEvents = dataHandler.nRawEvents();

    // Reserve memory for event stacks
    //Padplane padplane{"/home/nico/Desktop/padplane.geom"};
    //Tpc tpc{"/home/nico/Desktop/tpc.geom"};
    //State state{&padplane, &tpc};
    _pImpl->_pState->state()->reserveStacks(nRawEvents);

    // Create tasks
    PSATask psa{_pImpl->_pState->state()};

    // Loop over raw events in main thread
    //for (std::size_t iRawEvent = 0; iRawEvent < nRawEvents; ++iRawEvent)
    for (std::size_t iRawEvent = _pImpl->_fromEvent; iRawEvent < _pImpl->_fromEvent + _pImpl->_nEvents; ++iRawEvent)
    {
      auto nPads = dataHandler.nPads(iRawEvent); if (nPads == 0) continue;
      RawEvent rawEvent{iRawEvent, nPads};

      std::cout << "> read raw event: " << iRawEvent << " with " << nPads << " pads\n";

      for (std::size_t iPad = 0; iPad < nPads; ++iPad)
      {
	Pad pad;
	pad.setRawData(dataHandler.padRawData(iPad));
	rawEvent.addPad(std::move(pad));
      }
      dataHandler.endRawEvent();

      // Push raw event on stack
      _pImpl->_pState->state()->pushRawEvent(std::move(rawEvent));

      // Run tasks in parallel
      auto fEvent = taskSystem.async(&PSATask::run, psa, PSATask::MODE::BLSUB);
      futures.push_back(std::move(fEvent));
    }

    // Wait for all continuations to finish
    for (auto const& f : futures) f.wait();
  }
}
