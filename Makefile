# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2021/04/11 09:49:55 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MAINCODE = cub3d.c
GNLFOLDER = ./gnl/
MLXFOLDER = ./minilibx/
SRCFOLDER = ./src/
GNLCODE = get_next_line.c get_next_line_utils.c
GNL = $(addprefix $(GNLFOLDER), $(GNLCODE))
SRCCODE = init1.c init2.c load.c mloop.c finish.c keybrd.c \
			graph.c help1.c help2.c test.c move.c rayct1.c \
			rayct2.c rayct3.c sprite1.c sprite2.c bmp.c \
			color.c libft1.c libft2.c libft3.c exit.c valid1.c \
			valid2.c valid3.c file1.c file2.c file3.c
SRC = $(addprefix $(SRCFOLDER), $(SRCCODE))
CODE = $(MAINCODE) $(SRC) $(GNL)
FLAGS = -Wall -Wextra -Werror
MLXHEADER = -I $(MLXFOLDER)
MLXLIB = -L $(MLXFOLDER)
MLXFLAGS = -lmlx -lm -lX11 -lXext
MLX = $(MLXHEADER) $(MLXLIB) $(MLXFLAGS)
OUTPUT = cub3D
MAPFILE = map.cub
MEMLEAK = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(CODE) $(MLX) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

fclean:
	rm -f $(OUTPUT)

re:	fclean all

debug:
	gcc -g $(CODE) $(MLX) -o $(OUTPUT)

memleak:
	gcc -g $(MEMLEAK) $(CODE) $(MLX) -o $(OUTPUT)

run:
	./$(OUTPUT) $(MAPFILE)

save:
	./$(OUTPUT) $(MAPFILE) --save