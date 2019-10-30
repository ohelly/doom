# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/10/30 19:34:04 by glormell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

INC = -I $(FRAMEDIR)/SDL2.framework/Versions/A/Headers -I ./inc \
-I $(FRAMEDIR)/SDL2_image.framework/Versions/A/Headers \
-I $(FRAMEDIR)/SDL2_ttf.framework/Versions/A/Headers \
-I $(FRAMEDIR)/SDL2_mixer.framework/Versions/A/Headers \

FRAMEDIR = /Users/$(USER)/Library/Frameworks

FRAME = $(FRAMEDIR)/SDL2.framework $(FRAMEDIR)/SDL2_image.framework \
$(FRAMEDIR)/SDL2_mixer.framework $(FRAMEDIR)/SDL2_ttf.framework

FLAGS = -Wall -Werror -Wextra -Ofast -c

LIBS = lib

FLAGS2 = -g -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
-framework SDL2_ttf -framework SDL2_mixer -lftgnl -lft -lm

OBJ = src/main.o src/loadall.o src/countall.o src/loadsectors.o src/loadvertexes.o src/utils.o \
src/loadobjs.o src/loadobjs_hit.o src/loadobjs_hit_create.o src/loadobjs_collision.o src/loadobjs_collision_create.o src/loadpics.o src/loadplayer.o src/loadgame.o src/hooks.o src/profiling.o src/rgb_manipulations.o \
src/drawsprites.o src/drawscreen.o src/drawweapon.o src/vector_math.o src/object_triggers.o src/player_move.o \
src/colliders.o src/enemy.o src/enemy_action.o src/enemy_event.o src/enemy_event_framestart.o src/sounds.o src/drawhud.o src/loadhud.o src/loadfonts.o src/loadmap.o \
src/loadtexturedata.o src/loadweapondata.o src/loadobjdata.o src/loadpicdata.o src/loadimage.o src/loadparams.o \
src/doors.o src/calcmove.o src/calciswall.o src/calcjump.o src/animation.o src/drawscope.o src/drawsky.o \
src/drawwalls.o src/vline2.o src/vline3.o src/tomapcood.o src/scaler.o src/drawceilandfloor.o src/findscales.o \
src/render_walls.o src/calcpics.o src/intersect.o src/calcsector.o src/render_weapon.o src/weapon_utils.o src/vlineobj.o \
src/drawobj.o src/render_pics.o src/hooks_move.o src/hooks_weapons.o src/hooks_interact.o src/hooks_close.o src/shoot_wall.o \
src/mouse_hooks.o src/ft_strjoinc.o src/sound_free.o src/utils2.o src/vector_math2.o src/utils3.o \
src/loadmenu.o src/loadmenubuttons.o src/loadmenuclick.o src/drawmenu.o src/menu_mouse.o \
src/menu_click.o src/menu_hover.o src/menu_active.o src/menu_keys.o


all: $(FRAMEDIR) $(LIBS) $(FRAME) $(NAME)

$(NAME): $(OBJ)
	make -C Get_Next_Line
	gcc $(OBJ) -L $(LIBS) $(INC) $(FLAGS2) -o $(NAME)
	rm -rf ~/Documents/DoomNukem/
	mkdir ~/Documents/DoomNukem
	cp -r Resources/* ~/Documents/DoomNukem/
$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	make -C Get_Next_Line clean
	rm -f $(OBJ)

fclean: clean
	make -C Get_Next_Line fclean
	rm -f $(NAME)
	rm -rf $(FRAME)
	rm -rf ~/Documents/DoomNukem/

$(FRAMEDIR):
	mkdir $(FRAMEDIR)

$(FRAME): $(FRAMEDIR)/%: Frameworks/%
	cp -R $< $(FRAMEDIR)

$(LIBS):
	mkdir lib

re: fclean all
