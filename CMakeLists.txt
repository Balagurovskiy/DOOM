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
        inc/render_scaler.h
        inc/render_heights.h
        inc/render_wall.h
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
        src/render_towards.c
        src/render_wall.c
        src/render_wall_intersection.c
        src/render_line.c
        src/render_scaler.c
        src/render_heights.c
        src/render_floor_ceil.c
        src/render_perspective.c
                    src/event_mouse_view.c
                    src/utils_xyz.c
                    src/loader.c)
target_link_libraries(doom ${libsdl})
