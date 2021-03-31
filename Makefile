# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2021/03/31 11:14:07 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAINCODE = cub3d.c
GNLFOLDER = ./gnl/
MLXFOLDER = ./minilibx/
SRCFOLDER = ./src/
GNLCODE = get_next_line.c get_next_line_utils.c
GNL = $(addprefix $(GNLFOLDER), $(GNLCODE))
SRCCODE = init1.c init2.c load.c mloop.c finish.c keybrd.c \
			graph.c help1.c help2.c test.c move.c rayct1.c \
			rayct2.c rayct3.c sprite.c bmp.c color.c libft1.c \
			libft2.c libft3.c exit.c valid1.c valid2.c file1.c \
			file2.c
SRC = $(addprefix $(SRCFOLDER), $(SRCCODE))
CODE = $(MAINCODE) $(SRC) $(GNL)
FLAGS = -Wall -Wextra -Werror
MLXHEADER = -I $(MLXFOLDER)
MLXLIB = -L $(MLXFOLDER)
MLXFLAGS = -lmlx -lm -lX11 -lXext
MLX = $(MLXHEADER) $(MLXLIB) $(MLXFLAGS)
OUTPUT = cub3d.out
MAPFILE = map.cub
MEMLEAK = -fsanitize=address

build:
	gcc $(FLAGS) $(CODE) $(MLX) -o $(OUTPUT)

debug:
	gcc -g $(CODE) $(MLX) -o $(OUTPUT)

memleak:
	gcc -g $(MEMLEAK) $(CODE) $(MLX) -o $(OUTPUT)

run:
	./$(OUTPUT) $(MAPFILE)

save:
	./$(OUTPUT) $(MAPFILE) --save

clean:
	rm *.out