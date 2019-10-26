/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:21:32 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/26 11:32:29 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_music(t_doom *doom)
{
	t_music *m;
	t_sound *s;

	m = &doom->music[0];
	m->music = Mix_LoadMUS("./music.mp3");
	m->volume = 0;
	s = &doom->sound[SOUND_SHOOT];
	s->sound = Mix_LoadWAV("hit.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_PICKUP];
	s->sound = Mix_LoadWAV("pickup.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_WEAPON_PICKUP];
	s->sound = Mix_LoadWAV("weapon_pick.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_DEATH];
	s->sound = Mix_LoadWAV("death.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_INTERACT];
	s->sound = Mix_LoadWAV("interact.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_E_ATTACK];
	s->sound = Mix_LoadWAV("enemy_attack.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_LOSS];
	s->sound = Mix_LoadWAV("lost.wav");
	s->volume = 100;
	s = &doom->sound[SOUND_RELOAD];
	s->sound = Mix_LoadWAV("reload.wav");
	s->volume = 100;
	printf("Music loaded!\n");
}

int		play_sound(t_doom *doom, int index)
{
	Mix_Chunk	*sound;
	int			ch;

	if (index >= 10 || index < 0)
		return (0);
	sound = doom->sound[index].sound;
	ch = Mix_PlayChannel(-1, sound, 0);
	Mix_Volume(ch, doom->sound[index].volume);
	return (1);
}

int		play_music(t_doom *doom, int index)
{
	Mix_Music *music;

	if (index >= 2 || index < 0)
		return (0);
	music = doom->music[index].music;
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(doom->music[index].volume);
}

int		sound_free_everything(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < 2)
		Mix_FreeMusic(doom->music[i].music);
	i = -1;
	while (++i < 10)
		Mix_FreeChunk(doom->sound[i].sound);
	return (1);
}
