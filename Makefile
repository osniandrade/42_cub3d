# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2021/03/23 13:14:50 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAINCODE = cub3d.c
GNLFOLDER = ./gnl/
MLXFOLDER = ./minilibx/
GNLCODE = get_next_line.c get_next_line_utils.c
GNL = $(addprefix $(GNLFOLDER), $(GNLCODE))
SIDECODE = functions.c helper.c testing.c loadfile.c bmp.c
CODE = $(MAINCODE) $(SIDECODE) $(GNL)
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