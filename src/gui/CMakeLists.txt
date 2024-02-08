# Copyright Xavier Beheydt. All rights reserved.

add_library(gui INTERFACE)
target_link_libraries(gui INTERFACE SDL2::SDL2)
target_include_directories(gui INTERFACE public)
