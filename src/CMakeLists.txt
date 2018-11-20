cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(ATTPCFE VERSION 0.1 LANGUAGES C CXX)

# To install libraries into proper locations on all platforms
include(GNUInstallDirs)

# Do not like that but gets rid of -std=gnu++11 that overwrites target_compile_features
# with -std=gnu++1z
set(CMAKE_CXX_STANDARD 17) 

# Define imported targets
# HDF5
find_package(HDF5 COMPONENTS C REQUIRED)
add_library(hdf5 SHARED IMPORTED)
set_property(TARGET hdf5 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${HDF5_C_INCLUDE_DIRS})
set_property(TARGET hdf5 PROPERTY IMPORTED_LOCATION ${HDF5_C_LIBRARY_hdf5})
get_target_property(hdf5_loc hdf5 LOCATION)
message(STATUS "> HDF5 library: ${hdf5_loc}")

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # For resources
set(CMAKE_PREFIX_PATH $ENV{QT_DIR}) 
find_package(Qt5Widgets 5.11 REQUIRED)
find_package(Qt5Charts 5.11 REQUIRED)
find_package(Qt5Gui 5.11 REQUIRED)
find_package(Qt5Core 5.11 REQUIRED)
get_target_property(QtWidgets_loc Qt5::Widgets LOCATION)
get_target_property(QtCharts_loc Qt5::Charts LOCATION)
get_target_property(QtGui_loc Qt5::Gui LOCATION)
get_target_property(QtCore_loc Qt5::Core LOCATION)
message(STATUS "> Qt5 Widgets library: ${QtWidgets_loc}")
message(STATUS "> Qt5 Charts library: ${QtCharts_loc}")
message(STATUS "> Qt5 Gui library: ${QtGui_loc}")
message(STATUS "> Qt5 Core library: ${QtCore_loc}")

# VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
#message(STATUS "> VTK include: ${VTK_INCLUDE_DIRS}")
#message(STATUS "> VTK lib: ${VTK_LIBRARIES}")
message(STATUS "> VTK use file: ${VTK_USE_FILE}")

# For CTest
enable_testing()


add_subdirectory(lib)
add_subdirectory(app)
