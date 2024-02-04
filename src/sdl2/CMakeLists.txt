# Copyright Xavier Beheydt. All rights reserved.

add_executable(SDL2_display_image public/SDL2_display_image.c)
# target_link_libraries(SDL2_display_image PRIVATE
#                       $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#                       $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
# target_link_libraries(SDL2_display_image PRIVATE
#                       $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

target_link_libraries(SDL2_display_image PRIVATE
                      SDL2::SDL2main
                      SDL2::SDL2
                      SDL2_image::SDL2_image)
