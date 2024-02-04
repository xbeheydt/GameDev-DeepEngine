# Copyright Xavier Beheydt. All rights reserved.

# TODO : Docs

## Includes
include(cmake/functions/log.cmake)
#! Includes

## Find package
find_package(Git REQUIRED)
if (NOT GIT_FOUND)
    log(FATAL_ERROR Git "executable not found!")
endif()
#! Find package

## Git macros
macro(git_fetch path)
    if (NOT EXISTS ${path})
        log(FATAL_ERROR Git "path '${path}' does not exist!"T)
    endif()
    exec_program(COMMAND ${GIT_EXECUTABLE} fetch
                 WORKING_DIRECTORY ${path}
                 RESULT_VARIABLE GIT_FETCH_RESULT)
    if (NOT GIT_FETCH_RESULT EQUAL 0)
        log(FATAL_ERROR Git "fetch repo '${path}' failed!")
    endif()
endmacro(git_fetch path)

macro(git_pull path)
    if (NOT EXISTS ${path})
        log(FATAL_ERROR Git "path '${path}' does not exist!"T)
    endif()
    exec_program(COMMAND ${GIT_EXECUTABLE} pull
                 WORKING_DIRECTORY ${path}
                 RESULT_VARIABLE GIT_PULL_RESULT)
    if (NOT GIT_FETCH_RESULT EQUAL 0)
        log(FATAL_ERROR Git "pull repo '${path}' failed!")
    endif()
endmacro(git_fetch path)

macro(git_clone url path)
    if (NOT EXISTS ${path})
        execute_process(COMMAND ${GIT_EXECUTABLE} clone ${url} ${path}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_CLONE_RESULT)
        if(NOT GIT_CLONE_RESULT EQUAL 0)
            log(FATAL_ERROR Git "clone repo '${url}' failed!")
        endif()
    else() # Git fetch
        # FIXME fetch and pull not run
        # git_fetch(${path})
        # git_pull(${path})
    endif()
endmacro(git_clone url path)
#! Git functions
