cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-O2 -g")
set(CMAKE_CXX_FLAGS "-O3")

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE IMPLEMENTATION_FILES include/*.ipp)
file(GLOB_RECURSE TEST_FILES test/*.cpp)

# binary
project(fluffy_chess)
add_executable(fluffy_chess ${SRC_FILES} ${HEADER_FILES} ${IMPLEMENTATION_FILES})
target_include_directories(fluffy_chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
