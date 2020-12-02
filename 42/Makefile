# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2020/12/02 15:34:12 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAINCODE = cub3d.c
SIDECODE = functions.c helper.c
CODE = $(MAINCODE) $(SIDECODE)
FLAGS = -Wall -Wextra -Werror
MLXHEADER = -I /usr/local/include/
MLXLIB = -L /usr/local/lib/
MLXFLAGS = -lmlx -lm -lX11 -lXext
OUTPUT = cub3d.out

build:
	gcc $(FLAGS) $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

debug:
	gcc -g $(MLXHEADER) $(CODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm *.out