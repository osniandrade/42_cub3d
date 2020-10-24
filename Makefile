# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/24 12:09:35 by ocarlos-          #+#    #+#              #
#    Updated: 2020/10/24 12:35:28 by ocarlos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d.out

SRC =	start.c

OBJ = 	start.o

FLAGS = -Wall -Wextra -Werror

MLXHEADER = -I /usr/local/include/

MLXLIB = -L /usr/local/lib/

MLXFLAGS = -lmlx -lm -lX11 -lXext

OPTIONS = -g

all : $(NAME)

$(NAME):
	@gcc $(FLAGS) $(MLXHEADER) $(SRC) $(MLXLIB) $(MLXFLAGS) -o $(NAME)

db:
	@gcc $(OPTIONS) $(MLXHEADER) $(SRC) $(MLXLIB) $(MLXFLAGS) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all