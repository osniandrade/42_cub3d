# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2021/02/18 15:31:53 by ocarlos-         ###   ########.fr        #
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
MEMLEAK = -fsanitize=address

build:
	gcc $(FLAGS) $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

debug:
	gcc -g $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

memleak:
	gcc -g $(MEMLEAK) $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT) $(MAPFILE)

clean:
	rm *.out