cmake_minimum_required(VERSION 3.13)
project(doom C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${doom_SOURCE_DIR}/cmake")

include_directories(inc/)
add_executable(doom inc/doom.h
                inc/defines.h
                inc/events.h
                inc/render.h
                inc/render_scaler.h
                inc/render_heights.h
                inc/render_wall.h
                inc/utils.h
                inc/parser.h
                inc/libft.h
        src/parser/ft_lib/for_each_gnl.c
        src/parser/ft_lib/get_next_line.c
        src/parser/map_sector_utils.c
        src/parser/map_vertex_utils.c
        src/parser/parser.c
        src/parser/parser_textures.c
        src/parser/parser_level.c
        src/parser/parser_sector.c
        src/parser/parser_str_utils.c
        src/parser/parsed_data_connector.c
        src/parser/connect_player.c
        src/parser/connect_sector.c
        src/parser/connect_sector_object.c
        src/parser/connect_level.c
        src/parser/parser_validation.c
        src/parser/parser_utils.c
        src/parser/ft_lib/ft_atoi.c
        src/parser/ft_lib/ft_lstnew.c
        src/parser/ft_lib/ft_list_add.c
        src/parser/ft_lib/ft_list_clear.c
        src/parser/ft_lib/ft_lst_delone.c
        src/parser/ft_lib/ft_memdel.c
        src/parser/ft_lib/ft_str_contains.c
        src/parser/ft_lib/ft_strlen.c
        src/parser/ft_lib/ft_strjoin.c
        src/parser/ft_lib/ft_strequ.c
        src/parser/ft_lib/ft_strchr.c
        src/parser/ft_lib/ft_strdel.c
        src/parser/ft_lib/ft_strdup.c
        src/parser/ft_lib/ft_strsub.c
        src/parser/ft_lib/ft_splinter.c
        src/parser/ft_lib/ft_putstr.c
        src/parser/ft_lib/ft_memcpy.c
                    src/main.c
                    src/music.c
                    src/texts.c
                    src/text_utils.c
                    src/free.c
                    src/action_utils.c
                    src/actions.c
                    src/event_key_collision.c
                    src/event_key_bumping.c
                    src/event.c
                    src/level.c
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
        )
