# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/23 19:23:50 by ohelly            #+#    #+#              #
#    Updated: 2019/09/01 17:42:46 by dtoy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom
CC = gcc
MAKE = make
#FLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -l SDL2-2.0.0
CFILES = \
		srcs/main.c \
		srcs/loadmap.c \
		srcs/get_next_line.c \
		srcs/loadsectors.c \
		srcs/sdlstart.c \
		srcs/hooks.c \
		srcs/drawgame.c \
		srcs/line.c
OFILES = $(CFILES:%.c=%.o)
LIBINC = libft/includes
LIBPATH = libft/
FT = ft
LFTPATH = $(LIBPATH)
LFT = $(addprefix lib, $(addsuffix .a, $(FT)))
LIBFT = -L$(LFTPATH) -l$(FT)
MKFT = $(MAKE) -C $(LFTPATH)
SRC = $(CFILES)
OBJS = $(OFILES)
INC = include/
SDL = includeSDL/
SDLlib = lib/
INCLUDES = -I$(LIBINC) -I$(INC) -I$(SDL)
LIB = -lm $(LIBFT) -L $(SDLlib)
all: $(NAME)
$(NAME) : $(LFT) $(OBJS)
		$(CC) -o $(NAME) $(INCLUDES) $(LIB) $(FRAMEWORKS) $(OBJS)
%.o: %.c
		$(CC) $(FLAGS) -o $@ $(INCLUDES) -c $<
$(LFT):
		$(MKFT)
clean:
		$(MKFT) clean
		rm -rf $(OBJS)
fclean: clean
		$(MKFT) fclean
		rm -rf $(NAME)
re: fclean all
