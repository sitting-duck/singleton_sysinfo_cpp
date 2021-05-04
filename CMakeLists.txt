cmake_minimum_required(VERSION 3.10)
project(singleton_example CXX)
set(PROJECT_DESCRIPTION "Simple singleton example with a sysinfo.")

# C++11 standard
set(CMAKE_CXX_STANDARD 11)

enable_language(OBJCXX)

# Thread package needed
find_package(Threads)

# C++ extra flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")


# Application Binary Interface version for library/application interfacing
set(ABI_VERSION_MAJOR "1")
set(ABI_VERSION_MINOR "0")
set(ABI_VERSION_PATCH "0")
set(ABI_VERSION "${ABI_VERSION_MAJOR}.${ABI_VERSION_MINOR}.${ABI_VERSION_PATCH}")

# Location for the builds
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY usr/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY usr/bin)

# SysInfo library
add_library(sysinfo SHARED include/SysInfo.h srcs/SysInfo.cpp)
add_library(macsysinfo SHARED include/MacSysInfo.h srcs/MacSysInfo.mm)
set_target_properties(sysinfo PROPERTIES VERSION ${ABI_VERSION} SOVERSION ${ABI_VERSION_MAJOR})


# SysInfo example executable
include_directories(include)
add_executable(main app/main.cpp)
set_target_properties(main PROPERTIES VERSION ${ABI_VERSION} SOVERSION ${ABI_VERSION_MAJOR})
target_link_libraries(main sysinfo macsysinfo ${CMAKE_THREAD_LIBS_INIT})
