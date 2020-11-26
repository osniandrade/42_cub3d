# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 15:20:32 by ocarlos-          #+#    #+#              #
#    Updated: 2020/11/26 08:33:36 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAINCODE = cub3d.c
TESTCODE = test.c
FLAGS = -Wall -Wextra -Werror
MLXHEADER = -I /usr/local/include/
MLXLIB = -L /usr/local/lib/
MLXFLAGS = -lmlx -lm -lX11 -lXext
OUTPUT = cub3d.out

build:
	gcc $(FLAGS) $(MLXHEADER) $(MAINCODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

debug:
	gcc -g $(MLXHEADER) $(MAINCODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT)

test:
	gcc -g $(MLXHEADER) $(MAINCODE) $(MLXLIB) $(MLXFLAGS) -o $(OUTPUT)

clean:
	rm $(OUTPUT)