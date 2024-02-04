# Copyright Xavier Beheydt. All rights reserved.

add_executable(SDL2_display_image public/SDL2_display_image.c)

target_link_libraries(SDL2_display_image PRIVATE
                      SDL2::SDL2main
                      SDL2::SDL2
                      SDL2_image::SDL2_image)
target_compile_definitions(SDL2_display_image
                           PRIVATE LETTUCE_IMAGE="${PROJECT_SOURCE_DIR}/assets/images/lettuce.png")


add_executable(SDL2_health_bar public/SDL2_health_bar.c)
target_link_libraries(SDL2_health_bar PRIVATE
                      SDL2::SDL2main
                      SDL2::SDL2
                      SDL2_image::SDL2_image)
target_compile_definitions(SDL2_health_bar
                           PRIVATE HEALTHBAR_IMAGE="${PROJECT_SOURCE_DIR}/assets/images/healthbar.png")
