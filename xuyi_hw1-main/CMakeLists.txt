cmake_minimum_required(VERSION 3.10.1)

project (main)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

aux_source_directory(src SRC_LIST)

include_directories(inc)

add_executable(main ${SRC_LIST})