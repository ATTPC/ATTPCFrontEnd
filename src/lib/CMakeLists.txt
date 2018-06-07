# Define ATTPC Front-End library
project(lib VERSION 0.1 LANGUAGES C CXX)

# ========================================================
# Define the core library
# ========================================================
add_library(attpcfelib SHARED
  src/hdf5_wrapper.cpp
  src/notification_queue.cpp
  src/task_system.cpp)

target_include_directories(attpcfelib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_compile_options(attpcfelib
  PUBLIC -std=c++17 -Wall -O2)

target_link_libraries(attpcfelib
  hdf5)

# 'make install' to the correct locations (provided by GNUInstallDirs)
install(TARGETS attpcfelib EXPORT ATTPCFELibConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ATTPCFELibConfig DESTINATION share/ATTPCFELib/cmake)

# This makes the project importable from the build directory
export(TARGETS attpcfelib FILE ATTPCFELibConfig.cmake)


# ========================================================
# Unit tests
# ========================================================
add_executable(hdf5_wrapper
    test/hdf5_wrapper_test.cpp)
target_link_libraries(hdf5_wrapper
  attpcfelib)
add_test(NAME hdf5_wrapper_test COMMAND hdf5_wrapper)

