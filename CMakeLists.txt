cmake_minimum_required(VERSION 3.9.0)
cmake_policy(VERSION 3.9.0)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

project(hdf-demo
        VERSION 1.0.0
        LANGUAGES CXX C)

find_package(HDF5 REQUIRED)

add_executable(write-array write-array.cpp)
target_compile_definitions(write-array PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(write-array PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(write-array ${HDF5_LIBRARIES})

add_executable(write-chunked-array write-chunked-array.cpp)
target_compile_definitions(write-chunked-array PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(write-chunked-array PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(write-chunked-array ${HDF5_LIBRARIES})

add_executable(read-array read-array.cpp)
target_compile_definitions(read-array PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(read-array PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(read-array ${HDF5_LIBRARIES})

add_executable(read-array-subset read-array-subset.cpp)
target_compile_definitions(read-array-subset PRIVATE ${HDF5_DEFINITIONS})
target_include_directories(read-array-subset PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(read-array-subset ${HDF5_LIBRARIES})
