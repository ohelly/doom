# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/06/19 20:10:10 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../../lib/libft.a

FLAGS = -Wall -Werror -Wextra -c

OBJ = ft_abs.o ft_atoi.o ft_atoi_base.o ft_bzero.o ft_cut.o ft_isalnum.o \
ft_isalpha.o ft_isascii.o ft_isdigit.o ft_islower.o ft_isprint.o \
ft_isspace.o ft_isupper.o ft_itoa.o ft_letter_counter.o ft_lstadd.o \
ft_lstdel.o ft_lstdelone.o ft_lstiter.o ft_lstmap.o ft_lstnew.o \
ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o \
ft_memdel.o ft_memmove.o ft_memset.o ft_pow.o ft_putchar.o \
ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o \
ft_putstr.o ft_putstr_fd.o ft_recharlloc.o ft_strcat.o ft_strchr.o \
ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strdel.o ft_strdup.o ft_strequ.o \
ft_striter.o ft_striteri.o ft_strjoin.o ft_strjoinfree.o ft_strlcat.o \
ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o \
ft_strncpy.o ft_strndup.o ft_strnequ.o ft_strnew.o ft_strnstr.o \
ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o \
ft_tolower.o ft_toupper.o ft_word_counter.o ft_sqrt.o\

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ): %.o: %.c
	gcc $(FLAGS) -I ../../inc $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
