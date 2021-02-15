# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2021/02/15 14:29:33 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAINCODE = cub3d.c
GNLCODE = get_next_line.c get_next_line_utils.c
SIDECODE = functions.c helper.c testing.c
CODE = $(MAINCODE) $(SIDECODE) $(GNLCODE)
FLAGS = -Wall -Wextra -Werror
MLXHEADER = -I ./minilibx/
MLXLIB = -L ./minilibx/
MLXFLAGS = -lmlx -lm -lX11 -lXext
OUTPUT = cub3d.out
MAPFILE = map.cub

build:
	gcc $(FLAGS) $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

debug:
	gcc -g $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT) $(MAPFILE)

clean:
	rm *.out