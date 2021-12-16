cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Fetch google tests.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Configure compiler flags.
enable_language(CXX)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -g -std=c++1z -fmax-errors=1 -Wno-sign-compare")
endif()

# Compile library
project(AoC2021)
set(days 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25)
set(source main.cpp common/common.hpp common/common.cpp)
foreach(dir IN ITEMS ${days})
  set(source ${source} ${dir}/${dir}.hpp ${dir}/${dir}.cpp)
endforeach()
add_library(lib ${source})
target_include_directories(lib PRIVATE common ${days})

# Compile executable.
set(source main.cpp)
add_executable(aoc21 main.cpp)
target_link_libraries(aoc21 lib)
target_include_directories(aoc21 PRIVATE common ${days})

# Configure tests.
enable_testing()

set(test_sources)
foreach(dir IN ITEMS ${days})
  set(test_sources ${test_sources} ${dir}/${dir}_tests.cpp)
endforeach()
add_executable(tests ${test_sources})
target_link_libraries(tests gtest_main lib)
target_include_directories(tests PRIVATE common ${days})

include(GoogleTest)
gtest_discover_tests(tests)

# Copy input and test_input files.
foreach(dir IN ITEMS ${days})
  foreach(file IN ITEMS input test_input)
    set(input ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${file})
    set(output ${CMAKE_CURRENT_BINARY_DIR}/${file}_${dir})
    add_custom_command(
      COMMENT "Updating input file for day ${dir}."
      DEPENDS ${input}
      OUTPUT ${output}
      COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
    )
    add_custom_target(${dir}_${file} DEPENDS ${output})
    add_dependencies(aoc21 ${dir}_${file})
  endforeach()
endforeach()
