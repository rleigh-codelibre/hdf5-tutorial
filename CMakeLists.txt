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

target_compile_definitions(demo1 PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(demo1 PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(demo1 ${HDF5_LIBRARIES})

add_executable(demo2 demo2.cpp)

target_compile_definitions(demo2 PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(demo2 PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(demo2 ${HDF5_LIBRARIES})

add_executable(demo3 demo3.cpp)

target_compile_definitions(demo3 PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(demo3 PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(demo3 ${HDF5_LIBRARIES})
