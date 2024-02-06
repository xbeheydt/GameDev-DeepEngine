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

add_executable(SDL2_sprite_anim public/SDL2_sprite_anim.c)
target_link_libraries(SDL2_sprite_anim PRIVATE
                      SDL2::SDL2main
                      SDL2::SDL2
                      SDL2_image::SDL2_image
                      SDL2_ttf::SDL2_ttf)
target_compile_definitions(SDL2_sprite_anim
                           PRIVATE SPRITE_IMAGE="${PROJECT_SOURCE_DIR}/assets/images/adventurer-sheet.png"
                           PRIVATE FONT_PATH="${PROJECT_SOURCE_DIR}/assets/fonts/ttf/Roboto-Regular.ttf"
                           )
