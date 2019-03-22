NAME = doom

FILES =  test

 
H = 	doom \
        defines\
        events \
        render_towards \
        utils \
		
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


$(OBJ): obj/%.o : src/%.c
	@gcc -o $@ $(FLAG2) $(HEADERS) $(INCLUDES) -c $<

clean:
	@rm -f $(OBJ)
	 

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ)
	 
re: fclean all