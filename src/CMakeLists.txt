cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

enable_language(CXX)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -g -std=c++1z -fmax-errors=1 -Wno-sign-compare")
endif()

project(AoC2021)
set(days 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25)
set(source main.cpp common/common.hpp common/common.cpp)
foreach(dir IN ITEMS ${days})
  set(source ${source} ${dir}/${dir}.hpp ${dir}/${dir}.cpp)
endforeach()

add_executable(aoc21 ${source})
target_include_directories(aoc21 PRIVATE common)
foreach(dir IN ITEMS ${days})
  target_include_directories(aoc21 PRIVATE ${dir})
endforeach()

foreach(dir IN ITEMS ${days})
  set(input ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/input)
  set(output ${CMAKE_CURRENT_BINARY_DIR}/input_${dir})
  add_custom_command(
    COMMENT "Updating input file for day ${dir}."
    DEPENDS ${input}
    OUTPUT ${output}
    COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
  )
  add_custom_target(${dir} DEPENDS ${output})
  add_dependencies(aoc21 ${dir})
endforeach()
