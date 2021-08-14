cmake_minimum_required(VERSION 3.10)

project(SillySynthesizer)

# C++17 is needed for std::filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(include_files "wavefile.h" "utils.h" "synthesizer.h")
set(source_files "main.cpp" "wavefile.cpp" "utils.cpp" "synthesizer.cpp")

add_executable(SillySynthesizer ${include_files} ${source_files})
include_directories(${PROJECT_SOURCE_DIR})
