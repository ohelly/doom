# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/10/29 13:40:40 by ohelly           ###   ########.fr        #
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

FLAGS = -Ofast -Wall -Werror -Wextra -c
#FLAGS = -Ofast -c

LIBS = ./lib

FLAGS2 = -F /Users/$(USER)/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
-framework SDL2_ttf -framework SDL2_mixer -lftgnl -lft -lm

OBJ = src/main.o src/ft_line.o src/key_and_mouse_press.o src/output.o \
src/put_canvas.o src/put_select.o src/math_line.o src/math_vectors.o \
src/math_helpers.o src/export.o src/line_intersect.o src/select.o src/build.o \
src/load_map.o src/build_portal.o src/move_map.o src/split_wall.o src/delete_action.o src/split_sectors.o \
src/load_img.o src/put_image_on_screen.o src/put_string_on_screen.o src/mouse_press.o src/my_itoa.o \
src/set_sprite_on_wall.o src/set_object.o src/init_all.o src/mouse_press_left.o \
src/additional_func.o src/check_convex.o src/sel_sector.o src/sel_wall.o src/mouse_press_right.o \
src/sel_attr.o src/sel_value.o src/sel_texture_wall.o src/change_skybox.o src/sel_object.o src/sel_sprite.o \
src/render_images.o src/edditing_img_render.o src/main_hud_for_edditing.o src/object_img_render.o \
src/helper_draw.o src/height_spr.o src/export_vert.o src/export_sector.o src/export_helper.o \
src/export_wall.o src/export_wall_rev.o src/sel_txtc.o src/sel_txtf.o src/init_preview.o \
src/sel_txt_spr.o src/sel_txt_obj.o src/set_player.o src/export_all_texture.o src/load_surface_wall.o \
src/export_wall_t.o src/export_ceil_tx.o src/export_floor_tx.o src/load_surface.o src/export_sky_tx.o \
src/export_shot_tx.o src/export_weapon_data.o src/load_weapon.o src/export_stobj_data.o src/load_st_obj.o \
src/load_pickobj.o src/output_text_stobj.o src/export_pics.o src/load_pics.o src/export_attr.o \
src/export_objs.o src/export_pospics.o src/export_player.o src/health_player.o src/load_sector.o \
src/load_obj_spr.o src/import_player.o src/load_sky.o \

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
