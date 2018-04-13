cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(ATTPCFE VERSION 0.1 LANGUAGES CXX)

# to install libraries into proper locations on all platforms
include(GNUInstallDirs)

# define imported targets
# HDF5
find_package(HDF5 REQUIRED COMPONENTS CXX HL)
add_library(hdf5cpp SHARED IMPORTED)
set_property(TARGET hdf5cpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})
set_property(TARGET hdf5cpp PROPERTY IMPORTED_LOCATION ${HDF5_CXX_LIBRARIES})
add_library(hdf5hl SHARED IMPORTED)
set_property(TARGET hdf5hl PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})
set_property(TARGET hdf5hl PROPERTY IMPORTED_LOCATION ${HDF5_CXX_HL_LIBRARIES})
get_target_property(hdf5cpp_location hdf5cpp LOCATION)
get_target_property(hdf5hl_location hdf5hl LOCATION)
message(STATUS "> HDF5 includes: ${HDF5_INCLUDE_DIRS}")
message(STATUS "> HDF5 C++ library: ${hdf5cpp_location}")
message(STATUS "> HDF5 C++ HL library: ${hdf5hl_location}")

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # for resources
set(CMAKE_PREFIX_PATH $ENV{QT_HOME}) 
find_package(Qt5Widgets 5.10 REQUIRED)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
find_package(Qt5Gui 5.10 REQUIRED)
get_target_property(QtGui_location Qt5::Gui LOCATION)
find_package(Qt5Core 5.10 REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
message(STATUS "> Qt5 Widgets includes: ${CMAKE_PREFIX_PATH}/include/QtWidgets")
message(STATUS "> Qt5 Widgets library: ${QtWidgets_location}")
message(STATUS "> Qt5 Gui includes: ${CMAKE_PREFIX_PATH}/include/QtGui")
message(STATUS "> Qt5 Gui library: ${QtGui_location}")
message(STATUS "> Qt5 Core includes: ${CMAKE_PREFIX_PATH}/include/QtCore")
message(STATUS "> Qt5 Core library: ${QtCore_location}")


#enable_testing()


#add_subdirectory(lib)
#add_subdirectory(app)
