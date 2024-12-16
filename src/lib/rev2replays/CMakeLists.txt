cmake_minimum_required (VERSION 3.9)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

file(GLOB SOURCES *.c)
add_library(librev2replays ${SOURCES})
