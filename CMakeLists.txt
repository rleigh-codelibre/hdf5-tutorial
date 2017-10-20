cmake_minimum_required(VERSION 3.9.0)
cmake_policy(VERSION 3.9.0)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

project(hdf-demo
        VERSION 1.0.0
        LANGUAGES CXX C)

find_package(HDF5 REQUIRED)

add_executable(demo1 demo1.cpp)

target_compile_definitions(demo PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(demo PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(demo ${HDF5_LIBRARIES})