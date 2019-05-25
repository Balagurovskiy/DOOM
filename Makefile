NAME = doom

FILES =  main \
        free \
        music \
        texts \
        text_utils \
        actions \
        action_utils \
        \
         event_key_collision \
         event_key_bumping \
         event_mouse_view \
         event \
         event_keys \
         event_key_moves \
         \
         utils_intersection \
         utils_point_side \
         utils_xyz \
         \
         render \
         render_towards \
         render_wall \
         render_wall_intersection \
         render_line \
         render_scaler \
         render_heights \
         render_floor_ceil \
         render_perspective \
         \
         parser/map_sector_utils \
         parser/map_vertex_utils \
         parser/parser \
         parser/parser_level \
         parser/parser_sector \
         parser/parser_str_utils \
         parser/parser_utils \
         parser/parsed_data_connector \
         parser/connect_player \
         parser/connect_sector \
         parser/connect_sector_object \
         parser/connect_level \
         parser/parser_validation \
         \
         parser/ft_lib/for_each_gnl \
         parser/ft_lib/get_next_line \
         parser/ft_lib/ft_atoi \
         parser/ft_lib/ft_lstnew \
         parser/ft_lib/ft_list_add \
         parser/ft_lib/ft_list_clear \
         parser/ft_lib/ft_lst_delone \
         parser/ft_lib/ft_memdel \
         parser/ft_lib/ft_str_contains \
         parser/ft_lib/ft_strlen \
         parser/ft_lib/ft_strjoin \
         parser/ft_lib/ft_strequ \
         parser/ft_lib/ft_strchr \
         parser/ft_lib/ft_strdel \
         parser/ft_lib/ft_strdup \
         parser/ft_lib/ft_splinter \
         parser/ft_lib/ft_putstr \
         parser/ft_lib/ft_memcpy \
         parser/ft_lib/ft_strsub

 
H = 	doom \
        defines\
        events \
        render \
        render_scaler \
        render_heights \
        render_wall \
        utils \
        parser \
        libft
		
HEADERS = -I./inc
#add
HDRS = $(addprefix inc/, $(addsuffix .h, $(H)))
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
#OBJ_LIST = $(addsuffix .o, $(FILES))
SPEED = -O3

FLAGS = -Wall -Wextra -Werror

INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer
 

all:  $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(FLAG) $(SPEED) $(OBJ) $(FRAMEWORKS) -g


$(OBJ): obj/%.o : src/%.c $(HDRS)
	@gcc -o $@ $(FLAG2) $(HEADERS) $(INCLUDES) -c $<

clean:
	@rm -f $(OBJ)
	 

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ)
	 
re: fclean all