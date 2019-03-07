cmake_minimum_required(VERSION 3.13)
project(doom C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_STANDARD 11)


find_library(libsdl SDL2 SDL2_image)
include_directories(inc/)
add_executable(doom inc/doom.h
                    inc/defines.h
                    inc/events.h
                    inc/render.h
                    inc/utils.h
                    src/main.c
                    src/event_key_collision.c
                    src/event_key_bumping.c
                    src/event.c
                    src/utils_intersection.c
                    src/event_keys.c
                    src/event_key_moves.c
                    src/utils_point_side.c
                    src/render.c
                    src/event_mouse_view.c
                    src/utils_xyz.c
                    src/loader.c)
target_link_libraries(doom ${libsdl})
