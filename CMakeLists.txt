cmake_minimum_required(VERSION 3.10)
project(bln_audio)

find_package(Threads REQUIRED)

option(BLN_AUDIO_TESTS "Enable Tests" OFF)
option(BLN_AUDIO_EXAMPLES "Enable Examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type" FORCE)
endif()

# Add external dependencies
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
add_compile_options(-Wno-deprecated-declarations)

add_subdirectory(third_party/bln_queue)
add_subdirectory(third_party/portaudio)

set(BUILD_TESTING OFF)
set(BUILD_REGTEST OFF)
set(BUILD_PROGRAMS OFF)
set(BUILD_EXAMPLES OFF)
set(ENABLE_CPACK OFF)
set(ENABLE_MPEG OFF)
set(ENABLE_EXTERNAL_LIBS OFF)
set(ENABLE_PACKAGE_CONFIG OFF)
set(INSTALL_PKGCONFIG_MODULE OFF)
add_subdirectory(third_party/libsndfile)

# Add lib bln_audio
add_library(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_sources(${PROJECT_NAME} PRIVATE
    include/bln_audio/all.hpp
    include/bln_audio/config.hpp
    include/bln_audio/player.hpp
    include/bln_audio/sink.hpp
    include/bln_audio/track.hpp
    include/bln_audio/types.hpp

    src/player.cpp
    src/sink.cpp
    src/track.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC
    bln_queue
    portaudio
    sndfile
    Threads::Threads
)

if (BLN_AUDIO_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if (BLN_AUDIO_EXAMPLES)
    add_subdirectory(example)
endif()
