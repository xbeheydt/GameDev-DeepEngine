# Copyright Xavier Beheydt. All rights reserved.

## TODO : Docs

## Includes
include(cmake/git.cmake)
#! Includes

## Variables
set(VCPKG_URL "https://github.com/microsoft/vcpkg.git")
set(VCPKG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg")
set(VCPKG_BOOTSTRAP "${VCPKG_PATH}/bootstrap-vcpkg")
if (WIN32)
    set(VCPKG_BOOTSTRAP "${VCPKG_BOOTSTRAP}.bat")
else()
    set(VCPKG_BOOTSTRAP "${VCPKG_BOOTSTRAP}.sh")
endif()
set(VCPKG_EXECUTABLE "${VCPKG_PATH}/vcpkg")
if (WIN32)
    set(VCPKG_EXECUTABLE "${VCPKG_EXECUTABLE}.exe")
endif()
set(VCPKG_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake")
#! Variables

## Vcpkg macros
macro(vcpkg_clone)
    git_clone(${VCPKG_URL} ${VCPKG_PATH})
endmacro(vcpkg_clone)

macro(vcpkg_run_bootstrap)
    if (NOT EXISTS ${VCPKG_EXECUTABLE})
        git_clone(${VCPKG_URL} ${VCPKG_PATH})
        execute_process(COMMAND ${VCPKG_BOOTSTRAP} -disableMetrics
                        WORKING_DIRECTORY ${VCPKG_PATH}
                        RESULT_VARIABLE VCPKG_BOOTSTRAP_RESULT)
        if(NOT VCPKG_BOOTSTRAP_RESULT EQUAL 0)
            log(FATAL_ERROR Vcpkg "bootstrap vcpkg failed!")
        endif()
    endif()
endmacro()
#! Vcpkg macros

## Main
vcpkg_clone()
vcpkg_run_bootstrap()
if (EXISTS VCPKG_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_FILE}
        CACHE STRING "Vcpkg toolchain file")
else()
    log(FATAL_ERROR Vcpkg "toolchain file not found!")
endif()
log(INFO Vcpkg " is installed!")
#! Main