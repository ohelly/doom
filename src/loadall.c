/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:21:04 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/15 21:34:39 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		**loadmap(void)
{
	int		fd;
	int		i;
	char	**map;
	char	*line;

	//printf("Start gnl\n");
	if ((fd = open("map-clear.txt", O_RDONLY)) == -1)
		return (0);
	i = 0;
	while (get_next_line(fd, &line))
		i++;
	if (!(map = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL);
	close(fd);
	fd = open("map-clear.txt", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(map[i] = ft_strdup(line)))
			return (NULL);
		i++;
		
	}
	map[i] = 0;
	close(fd);
	//printf("End gnl\n");
	return (map);
}

int		new_image(char *str, t_img *img, int w, int h)
{
	static int	ind = 0;
	float		tmp;
	int			j;

	j = 0;
	img[ind].data = (int*)ft_memalloc(sizeof(int) * w * h);
	img[ind].w = w;
	img[ind].h = h;
	printf("ind - %d\n", ind);
	while (j < w * h)
	{
		str = todigit(str, &tmp);
		img[ind].data[j] = (int)tmp;
		//printf("%d ", img[ind].data[j]);
		j++;
	}
	//printf("\n");
	return (ind++);
}

int		load_image(char *map, int *image, t_img *img)
{	
	int		w;
	int		h;
	float	tmp;

	map = todigit(map, &tmp); //image width
	w = (int)tmp;
	map = todigit(map, &tmp); //image height
	h = (int)tmp;
	*image = new_image(map, img, w, h);
	return (0);
}


t_texture	*load_texture(char **map, t_texture *txt, t_img *img)
{
	int		count;
	float	tmp;
	int		i;
	int		a;
	int		w;
	int		h;

	i = 0;
	//map[i] = todigit(map[i], &tmp);
	map[i] = todigit(map[i], &tmp);
	count = (int)tmp;
	printf("count - %d\n", count);
	txt = (t_texture*)ft_memalloc(sizeof(t_texture) * count);
	i = 1;
	a = 0;
	while (i <= count)
	{
		map[i] = todigit(map[i], &tmp); //image width
		w = (int)tmp;
		map[i] = todigit(map[i], &tmp); //image height
		h = (int)tmp;
		//printf("w - %d, h - %d\n", w, h);
		txt[a].image = new_image(map[i], img, w, h);
		printf("TXT - %d\n", txt[a].image);
		a++;
		i++;
	}
	return (txt);
}

int		load_texture_data(char **map, t_doom *doom)
{
	int		i;

	i = 0;
	while (*map[i] != '#')
	{
		//printf("Ok\n");
		if (*map[i] == 'S') //sky
		{
			doom->sky = load_texture(&map[i], doom->sky, doom->img);
			printf("sky img - %d\n", doom->sky[0].image);
		}
		if (*map[i] == 'W') //wall
		{
			doom->walls = load_texture(&map[i], doom->walls, doom->img);
			printf("walls img - %d, i - %d\n", doom->walls[0].image, i);
		}
		if (*map[i] == 'C') //ceil
		{
			//printf("%s\n", map[i]);
			doom->ceils = load_texture(&map[i], doom->ceils, doom->img);
			printf("ceils img - %d, i - %d\n", doom->ceils[0].image, i);	
		}
		if (*map[i] == 'F') //floor
		{
			doom->floors = load_texture(&map[i], doom->floors, doom->img);
			printf("floors img - %d\n", doom->floors[0].image);
		}
		i++;
	}
	return (0);
}

int		count_objs(char **map)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (*map[i] != '#')
		i++;
	i -= 2;
	count = atoi(map[i]);
	return (count);
}

int		count_params_obj(char *map, t_data *obj)
{
	float	tmp;
	int		n;
	int		a;
	int		w;
	int		h;

	map = todigit(map, &tmp);
	map = todigit(map, &tmp);
	obj->type = (int)tmp;
	map = todigit(map, &tmp);
	obj->states_count = (int)tmp;
	obj->images = (int**)ft_memalloc(sizeof(int*) * obj->states_count);
	obj->anim_count = (int*)ft_memalloc(sizeof(int) * obj->states_count);
	n = 0;
	while (n < obj->states_count)
	{
		map = todigit(map, &tmp);
		obj->anim_count[n] = (int)tmp;
		obj->images[n] = (int*)ft_memalloc(sizeof(int) * obj->anim_count[n]);
		n++;
	}
	return (0);
}

int		load_obj(char **map, t_data *obj, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_obj(map[i], obj);
	while (n < obj->states_count)
	{
		a = 0;
		while (a < obj->anim_count[n])
		{
			load_image(map[i + t], &obj->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_obj_data(char **map, t_doom *doom)
{
	int		i;
	int		t;
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	//doom->num.objs = count;
	doom->objs_data = (t_data*)ft_memalloc(sizeof(t_data) * (count + 1));
	i = 1;
	while (*map[i] != '#')
	{
		load_obj(&map[i], &doom->objs_data[atoi(map[i])], doom->img);
		while (*map[i] != '.')
		{
			if (*map[i] == '#')
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}

int		count_params_pic(char *map, t_data *pic)
{
	float	tmp;
	int		n;
	int		a;
	int		w;
	int		h;

	map = todigit(map, &tmp);
	map = todigit(map, &tmp);
	pic->type = (int)tmp;
//	printf("pic type - %d\n", pic->type);
	map = todigit(map, &tmp);
	pic->states_count = (int)tmp;
//	printf("pic states - %d\n", pic->states_count);
	pic->images = (int**)ft_memalloc(sizeof(int*) * pic->states_count);
	pic->anim_count = (int*)ft_memalloc(sizeof(int) * pic->states_count);
	n = 0;
	while (n < pic->states_count)
	{
		map = todigit(map, &tmp);
		pic->anim_count[n] = (int)tmp;
		//printf("anim - %d\n", pic->anim_count[n]);
		pic->images[n] = (int*)ft_memalloc(sizeof(int) * pic->anim_count[n]);
		n++;
	}
	return (0);
}

int		load_pic(char **map, t_data *pic, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_pic(map[i], pic);
	while (n < pic->states_count)
	{
		a = 0;
		while (a < pic->anim_count[n])
		{
			load_image(map[i + t], &pic->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_pic_data(char **map, t_doom *doom)
{
	int		i;
	int		t;
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	//doom->num.pics = count;
	doom->pics_data = (t_data*)ft_memalloc(sizeof(t_data) * (count + 1));
	i = 1;
	while (*map[i] != '#')
	{
		load_pic(&map[i], &doom->pics_data[atoi(map[i])], doom->img);
		while (*map[i] != '.')
		{
			if (*map[i] == '#')
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}

int		count_params_weapon(char *map, t_weapon *weapon)
{
	float	tmp;
	int		n;
	int		a;

	//map = todigit(map, &tmp);
	map = todigit(map, &tmp);
	weapon->type = (int)tmp;
//	printf("pic type - %d\n", pic->type);
	map = todigit(map, &tmp);
	weapon->states_count = (int)tmp;
//	printf("pic states - %d\n", pic->states_count);
	weapon->images = (int**)ft_memalloc(sizeof(int*) * weapon->states_count);
	weapon->anim_count = (int*)ft_memalloc(sizeof(int) * weapon->states_count);
	n = 0;
	while (n < weapon->states_count)
	{
		map = todigit(map, &tmp);
		weapon->anim_count[n] = (int)tmp;
		//printf("anim - %d\n", pic->anim_count[n]);
		weapon->images[n] = (int*)ft_memalloc(sizeof(int) * weapon->anim_count[n]);
		n++;
	}
	return (0);
}

int		load_weapon(char **map, t_weapon *weapon, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_weapon(map[i], weapon);
	weapon->delay = 0.035f;
	
	while (n < weapon->states_count)
	{
		a = 0;
		while (a < weapon->anim_count[n])
		{
			load_image(map[i + t], &weapon->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_weapon_data(char **map, t_doom *doom)
{
	int		i;
	int		t;
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	doom->num.weapons = count;
	doom->weapon = (t_weapon*)ft_memalloc(sizeof(t_weapon) * (count + 1));
	i = 1;
	while (*map[i] != '#')
	{
		load_weapon(&map[i], &doom->weapon[atoi(map[i])], doom->img);
		while (*map[i] != '.')
		{
			if (*map[i] == '#')
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}

int		load_data(t_doom *doom, char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (ft_strcmp(map[i], "texture_data") == 0)
			load_texture_data(&map[i + 1], doom);
		if (ft_strcmp(map[i], "weapon_data") == 0)
			load_weapon_data(&map[i + 1], doom);
		if (ft_strcmp(map[i], "obj_data") == 0)
			load_obj_data(&map[i + 1], doom);
		if (ft_strcmp(map[i], "pic_data") == 0)
			load_pic_data(&map[i + 1], doom);
		i++;
	}
	return (0);
}

int		load_params(t_doom *doom, char **map)
{
	int		i;
	t_xy	*v;
	
	countall(doom, map);
	if (!(v = (t_xy*)ft_memalloc(sizeof(t_xy) * doom->num.vertexes)))
		return (0);
	if (!(doom->sectors = (t_sectors*)ft_memalloc(sizeof(t_sectors) * doom->num.sectors)))
		return (0);
	if (!(doom->item = (t_item*)ft_memalloc(sizeof(t_item) * doom->num.sectors)))
		return (0);
	if (!(doom->objs = (t_obj*)ft_memalloc(sizeof(t_obj) * doom->num.objs)))
		return (0);
	if (!(doom->pics = (t_pics*)ft_memalloc(sizeof(t_pics) * doom->num.pics)))
		return (0);
	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], "Vertex", 5) == 0)
			loadvertexes(v, map[i]);
		else if (ft_strncmp(map[i], "Sector", ft_strlen("sector")) == 0)
		{
			if (!(loadsectors(doom->sectors, v, map[i])))
				return (0);
		}
		else if (ft_strncmp(map[i], "Objs", ft_strlen("objs")) == 0)
			loadobjs(doom, doom->objs, doom->objs_data, map[i]);
		else if (ft_strncmp(map[i], "Pics", ft_strlen("pic")) == 0)
			loadpics(doom ,doom->pics, doom->pics_data, map[i]);
		else if (ft_strncmp(map[i], "Player", ft_strlen("player")) == 0)
			loadplayer(&doom->player, map[i]);
		i++;
	}
	doom->player.where.z = doom->sectors[doom->player.sector].floor + EyeHeight;
	free(v);
	return (0);
}

int		loadall(t_doom *doom)
{
	char	**map;
	int		j;

	j = 0;
	if (!(map = loadmap()))
		return (0);
	//printf("Map loaded.\n");
	load_data(doom, map);
	load_params(doom, map);
	
	
	
		/*
	if (!(doom->len = (float*)ft_memalloc(sizeof(float) * doom->numobjs)))
		return (0);
	
	if (!(doom->txt = (t_texture*)ft_memalloc(sizeof(t_texture) * 1))) //нужно посчитать кол-во текстур
		return (0);
	if (!(loaddata(doom, map)))
		return (0);
	while (j < doom->numsectors)
	{
		printf("txtw - %d\n", doom->sector[j].txtw);		
		j++;
	}*/
	return (1);
}