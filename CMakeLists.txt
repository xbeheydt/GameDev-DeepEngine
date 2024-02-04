# Copyright Xavier Beheydt. All rights reserved.
cmake_minimum_required(VERSION 3.22)

## CMake configuration
# set the module path, used for includes
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
#! CMake configuration

## Log functions
include("cmake/functions/log.cmake")

## Install and Setting VCPKG
include("cmake/vcpkg.cmake")

project(DeepEngine VERSION 0.0.1
        DESCRIPTION "Yet another open source 3D game engine."
        LANGUAGES C CXX)

## Project presets
include("cmake/presets.cmake")

## External dependencies
include("cmake/extern/common.cmake")

add_subdirectory("src")
