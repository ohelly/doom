# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/09/12 19:06:31 by ohelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-editor

INC = -I $(FRAMEDIR)/SDL2.framework/Versions/A/Headers -I ./inc \
-I $(FRAMEDIR)/SDL2_image.framework/Versions/A/Headers \
-I $(FRAMEDIR)/SDL2_ttf.framework/Versions/A/Headers \
-I $(FRAMEDIR)/SDL2_mixer.framework/Versions/A/Headers \

FRAMEDIR = /Users/$(USER)/Library/Frameworks

FRAME = $(FRAMEDIR)/SDL2.framework $(FRAMEDIR)/SDL2_image.framework \
$(FRAMEDIR)/SDL2_mixer.framework $(FRAMEDIR)/SDL2_ttf.framework

#FLAGS = -Ofast -Wall -Werror -Wextra -c
FLAGS = -Ofast -c

LIBS = ./lib

FLAGS2 = -F /Users/$(USER)/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
-framework SDL2_ttf -framework SDL2_mixer -lftgnl -lft -lm

OBJ = src/main.o src/ft_line.o src/key_and_mouse_press.o src/output.o \
src/put_canvas.o src/put_select.o src/math_line.o src/math_vectors.o \
src/math_helpers.o src/export.o src/line_intersect.o src/select.o src/build.o \
src/load_map.o

all: $(FRAMEDIR) $(LIBS) $(FRAME) $(NAME)

$(NAME): $(OBJ)
	make -C Get_Next_Line
	gcc $(OBJ) -L $(LIBS) $(INC) $(FLAGS2) -o $(NAME)

$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	make -C Get_Next_Line clean
	rm -f $(OBJ)

fclean: clean
	make -C Get_Next_Line fclean
	rm -f $(NAME)
	rm -rf $(FRAME)

$(FRAMEDIR):
	mkdir $(FRAMEDIR)

$(FRAME): $(FRAMEDIR)/%: Frameworks/%
	cp -R $< $(FRAMEDIR)

$(LIBS):
	mkdir lib

re: fclean all
