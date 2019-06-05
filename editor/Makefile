# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/05 11:23:29 by mkachano          #+#    #+#              #
#    Updated: 2019/06/04 20:28:31 by obalagur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../level_editor

SRC_DIR :=	./src/
OBJ_DIR :=	./obj/
INC_DIR :=	./include/
LIB_DIR :=	./

SRC =               main.c \
                    button.c \
                    error_libs.c \
                    error_file.c \
                    init_app.c \
                    image_loader.c \
                    render_app.c \
                    utils.c \
                    render_line.c \
                    save_level_map.c \
                    intersection.c \
                    shape.c \
                    render_point.c \
                    render_shape.c \
                    shape_neighbors.c \
                    shape_neighbors2.c \
                    shape_optimization.c \
                    event_mouse_handle.c \
                    render_text.c \
                    menu_panel.c \
                    game.c \


#	project object files
OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#	libraries
#libft
LIBFT = 		$(LIBFT_DIR)libft.a
LIBFT_DIR :=	$(LIB_DIR)libft/
LIBFT_FLAGS := 	-lft -L $(LIBFT_DIR)

# SDL_FLAGS	=	-I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks
INCLUDES	=	-I $(INC_DIR)\
				-I ../frameworks/SDL2.framework/Versions/A/Headers \
				-I ../frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I ../frameworks/SDL2_image.framework/Versions/A/Headers \
				-I ../frameworks/SDL2_mixer.framework/Headers \
				-F ../frameworks

# OGL_FLAGS	=	-framework OpenGL -framework AppKit
FRAMEWORKS	=	-F ../frameworks \
				-rpath ../frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

# SDL_FRM = -framework SDL2 -F /Library/Frameworks/ ./SDL2_ttf/SDL2_ttf

# SDL_INC = -I /Library/Frameworks/SDL2.framework/Headers/ -I SDL_ttf/

LINK_FLAGS := $(LIBFT_FLAGS)
CC_FLAGS := -Wall -Wextra -Werror -O3

all:
	@make -C $(LIBFT_DIR)
	@make $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INC_DIR)
	@gcc $(OBJ) $(LINK_FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORKS)
	@echo "Ready!"

$(OBJ_DIR)%.o: %.c
	@gcc -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS) $(INCLUDES)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)
