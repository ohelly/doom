# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/06/19 19:58:25 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../lib/libftgnl.a

INC = ../inc

FLAGS = -Wall -Werror -Wextra -c

OBJ = get_next_line.o

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	ar rc $(NAME) $(OBJ) ../lib/libft.a
	

$(OBJ): %.o: %.c
	gcc $(FLAGS) -I$(INC) $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
