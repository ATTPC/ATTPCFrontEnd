# Define ATTPC Front-End library
project(lib VERSION 0.1 LANGUAGES C CXX)

# ========================================================
# Define the core library
# ========================================================
add_library(attpcfelib SHARED
  src/core/Hdf5Wrapper.cpp
  src/core/ReconstructionState.cpp
  src/core/Pad.cpp
  src/core/RawEvent.cpp
  src/core/Hit.cpp
  src/core/HitList.cpp
  src/core/Event.cpp
  src/core/RawTrack.cpp
  src/core/PatternEvent.cpp
  src/core/Track.cpp
  src/core/TrackEvent.cpp
  src/core/Padplane.cpp
  src/core/Tpc.cpp
  src/reco/BaselineCorrection.cpp
  src/reco/PSATask.cpp
  src/reco/PatRecTask.cpp
  src/reco/TrackRecTask.cpp
  src/utils/NotificationQueue.cpp
  src/utils/TaskSystem.cpp
  src/utils/Active.cpp
  src/utils/Logger.cpp
  src/utils/LogMsg.cpp
  src/utils/LogLevel.cpp
  src/utils/LogSink.cpp)

target_include_directories(attpcfelib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(attpcfelib
  PRIVATE -Wall -O2)

target_compile_features(attpcfelib
  PRIVATE cxx_std_17)

target_link_libraries(attpcfelib
  hdf5)

# 'make install' to the correct locations (provided by GNUInstallDirs)
include(GNUInstallDirs)
install(TARGETS attpcfelib
    EXPORT ATTPCFELibConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ATTPCFELibConfig
  DESTINATION share/ATTPCFELib/cmake)

# This makes the project importable from the build directory
export(TARGETS attpcfelib FILE ATTPCFELibConfig.cmake)

# ========================================================
# Define the gui library
# (include all headers with the Q_OBJECT macro)
# ========================================================
add_library(attpcguilib SHARED
  src/gui/MainWindow.cpp
  src/gui/Display.cpp
  src/gui/DisplayFunctions.cpp
  src/gui/ReconstructionDock.cpp
  src/gui/ReconstructionDockTasks.cpp
  src/gui/ReconstructionDockState.cpp	
  include/gui/MainWindow.hpp
  include/gui/Display.hpp
  include/gui/DisplayFunctions.hpp
  include/gui/ReconstructionDock.hpp
  include/gui/ReconstructionDockTasks.hpp
  include/gui/ReconstructionDockState.hpp)

target_include_directories(attpcguilib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(attpcguilib
  PRIVATE -Wall -O2 -fPIC)

target_compile_features(attpcguilib
  PRIVATE cxx_std_17)

target_link_libraries(attpcguilib
   Qt5::Widgets
   Qt5::Charts
   Qt5::Gui
   Qt5::Core)
#   ${VTK_LIBRARIES})

install(TARGETS attpcguilib EXPORT ATTPCGUILibConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # this is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ATTPCGUILibConfig DESTINATION share/ATTPCGUILib/cmake)

export(TARGETS attpcguilib FILE ATTPCGUILibConfig.cmake)

# ========================================================
# Unit tests
# ========================================================
add_executable(hdf5_wrapper
    test/Hdf5WrapperTest.cpp)
target_link_libraries(hdf5_wrapper
    attpcfelib ${VTK_LIBRARIES})
add_test(NAME hdf5_wrapper_test COMMAND hdf5_wrapper)

add_executable(task_system
    test/TaskSystemTest.cpp)
target_link_libraries(task_system
  attpcfelib ${VTK_LIBRARIES})
add_test(NAME task_system_test COMMAND task_system)

add_executable(logger
    test/LoggerTest.cpp)
target_link_libraries(logger
  attpcfelib ${VTK_LIBRARIES})
add_test(NAME logger_test COMMAND logger)
