cmake_minimum_required(VERSION 3.16)
project(whisper_stream_app
  DESCRIPTION "whisper wrapper"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake")

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(WHISPER REQUIRED whisper)

find_package(SndFile REQUIRED)

include_directories(include)
include_directories(${SNDFILE_INCLUDE_DIR})

set(MAIN_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set(WHISPER_CLIENT_CPP_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/whisper_client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/whisper_client.hpp
)

add_library(whisper_client)
target_sources(whisper_client
  PRIVATE
  ${WHISPER_CLIENT_CPP_SOURCES}
  PUBLIC ${WHISPER_INCLUDE_DIRS})
target_include_directories(whisper_client
  PRIVATE
  include
)
target_link_libraries(whisper_client
#  PRIVATE SndFile::SndFile
  ${WHISPER_LIBRARIES}
)

add_executable(whisper_example)
target_sources(whisper_example
  PRIVATE
  ${MAIN_SOURCES}
)
target_include_directories(whisper_example
  PRIVATE
  include
)
target_link_libraries(whisper_example
  PRIVATE
  SndFile::SndFile
)
