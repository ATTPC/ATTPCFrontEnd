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

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;
using namespace attpcfe;

/*
void ProcessRawEvent() {

  RawEvent rawEvent;
  State::Instance().PopRawEvent(rawEvent);
  
  Event event{rawEvent.Id(), rawEvent.NPads()};

  for (auto const& pad : rawEvent.Pads())
  {
    HitList hits;

    double charge = 1.0;
    std::vector<double> pos{0., 0., 0.};
    Hit hit{std::move(pos), charge};
    hits.AddHit(std::move(hit));
    
    event.AddHitList(std::move(hits));
  }

  std::cout << "> ProcessRawEvent: " << rawEvent.Id() << ' ' << std::this_thread::get_id() << '\n';

  State::Instance().PushEvent(std::move(event));
}

void ProcessEvent() {

  Event event;
  State::Instance().PopEvent(event);

  PatternEvent patternEvent{event.Id()};

  std::cout << "> ProcessEvent: " << event.Id() << ' ' << std::this_thread::get_id() << '\n';
  std::this_thread::sleep_for(0.001s);

  State::Instance().PushPatternEvent(std::move(patternEvent));
}

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
  dataHandler.Open("/home/nico/Downloads/perico.h5");
  auto nRawEvents = dataHandler.NRawEvents();

  // Reserve memory for event stacks
  auto state = std::make_shared<State>();
  state->ReserveStacks(nRawEvents);

  // Create tasks
  PSATask psa{state};

  // Loop over raw events in main thread
  for (std::size_t iRawEvent = 0; iRawEvent < nRawEvents; ++iRawEvent)
  {
    auto nPads = dataHandler.NPads(iRawEvent); if (nPads == 0) continue;
    RawEvent rawEvent{iRawEvent, nPads};

    std::cout << "> read raw event: " << iRawEvent << " with " << nPads << "pads\n";

    for (std::size_t iPad = 0; iPad < nPads; ++iPad)
    {
      Pad pad;
      pad.SetRawData(dataHandler.PadRawData(iPad));
      rawEvent.AddPad(std::move(pad));
    }
    dataHandler.EndRawEvent();

    // Push raw event on stack
    state->PushRawEvent(std::move(rawEvent));

    // Run tasks in parallel
    auto fEvent = taskSystem.Async(&PSATask::Execute, psa, PSATask::MODE::BLSUB);
    futures.push_back(std::move(fEvent));
    
    //auto fEvent = taskSystem.Async(ProcessRawEvent);
    //auto fPatternEvent = taskSystem.Then(fEvent, ProcessEvent);
    //auto fTrackEvent = taskSystem.Then(fPatternEvent, ProcessPatternEvent, 2);
    //futures.push_back(std::move(fTrackEvent));
  }

  // Wait for all continuations to finish
  for (auto const& f : futures) f.wait();

  //std::cout << "> " << State::Instance().NTrackEvents() << " track events on stack\n";
  
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration<double>{end - start};
  std::cout << "> ATTPCFE app:MESSAGE, elapsed time: " << duration.count() << "s\n";
  
  return 0;
}
