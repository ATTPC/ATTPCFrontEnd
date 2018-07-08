#include <core/DataHandler.hpp>
#include <core/Hdf5Wrapper.hpp>
#include <core/TaskSystem.hpp>
#include <core/State.hpp>
#include <core/Pad.hpp>
#include <core/RawEvent.hpp>
#include <core/Hit.hpp>
#include <core/HitList.hpp>
#include <core/Event.hpp>
#include <core/PatternEvent.hpp>
#include <core/TrackEvent.hpp>
#include <reco/PSATask.hpp>
#include <reco/PatRecTask.hpp>
#include <reco/TrackRecTask.hpp>

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;
using namespace attpcfe;

/*

void ProcessPatternEvent(int n)
{
  PatternEvent patternEvent;
  State::Instance().PopPatternEvent(patternEvent);

  TrackEvent trackEvent{patternEvent.Id()};

  std::cout << "> ProcessPatternEvent: " << patternEvent.Id() << ' ' << std::this_thread::get_id() << ' ' << n << '\n';
  std::this_thread::sleep_for(0.001s);

  State::Instance().PushTrackEvent(std::move(trackEvent));
}
*/

int main(int argc, char* argv[]) {

  auto start = std::chrono::system_clock::now();

  // Create task system
  TaskSystem taskSystem;
  std::vector<std::future<void>> futures;

  // Open input file with data handler
  DataHandler<Hdf5Wrapper> dataHandler;
  dataHandler.open("/home/nico/Downloads/perico.h5");
  auto nRawEvents = dataHandler.nRawEvents();

  // Reserve memory for event stacks
  auto state = std::make_shared<State>();
  state->reserveStacks(nRawEvents);

  // Create tasks
  PSATask psa{state};
  PatRecTask patRec{state};
  TrackRecTask trackRec{state};

  auto count = 0;

  // Loop over raw events in main thread
  for (std::size_t iRawEvent = 0; iRawEvent < nRawEvents; ++iRawEvent)
  {
    auto nPads = dataHandler.nPads(iRawEvent); if (nPads == 0) continue;
    RawEvent rawEvent{iRawEvent, nPads};
    ++count;
    std::cout << "> read raw event: " << iRawEvent << " with " << nPads << "pads\n";

    for (std::size_t iPad = 0; iPad < nPads; ++iPad)
    {
      Pad pad;
      pad.setRawData(dataHandler.padRawData(iPad));
      rawEvent.addPad(std::move(pad));
    }
    dataHandler.endRawEvent();

    // Push raw event on stack
    state->pushRawEvent(std::move(rawEvent));

    // Run tasks in parallel
    auto fEvent = taskSystem.async(&PSATask::run, psa, PSATask::MODE::BLSUB);
    auto fPatternEvent = taskSystem.then(fEvent, &PatRecTask::run, patRec);
    auto fTrackEvent = taskSystem.then(fPatternEvent, &TrackRecTask::run, trackRec);
    futures.push_back(std::move(fTrackEvent));
  }

  // Wait for all continuations to finish
  for (auto const& f : futures) f.wait();

  std::cout << "> " << state->nTrackEvents() << " track events on stack\n";

  std::cout << "> " << count << " raw events\n";
  
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration<double>{end - start};
  std::cout << "> ATTPCFE app:MESSAGE, elapsed time: " << duration.count() << "s\n";
  
  return 0;
}
