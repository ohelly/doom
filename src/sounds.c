/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:21:32 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/26 15:46:10 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_music(t_doom *doom)
{
	t_music *m;
	t_sound *s;
	char	*env;

	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	m = &doom->music[0];
	m->music = Mix_LoadMUS(ft_strjoin(env, "/music.mp3"));
	m->volume = 0;
	s = &doom->sound[SOUND_SHOOT];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/hit.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_PICKUP];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/pickup.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_WEAPON_PICKUP];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/weapon_pick.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_DEATH];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/death.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_INTERACT];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/interact.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_E_ATTACK];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/enemy_attack.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_LOSS];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/lost.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_RELOAD];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/reload.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_SCREAM];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/scream.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_JUMP];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/jump.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_DAMAGE];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/damage.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_PISTOL];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/pistol.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_SHOTGUN];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/shotgun.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_RIPPER];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/ripper.wav"));
	s->volume = 70;
	s = &doom->sound[SOUND_FOOT];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/foot.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_EXPLOSIVE];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/explosion.wav"));
	s->volume = 100;
	s = &doom->sound[SOUND_CRASH];
	s->sound = Mix_LoadWAV(ft_strjoin(env, "/crash.wav"));
	s->volume = 100;
	printf("Music loaded!\n");
}

int		play_sound(t_doom *doom, int index)
{
	Mix_Chunk	*sound;
	int			ch;

	if (index >= 17 || index < 0)
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
	while (++i < 17)
		Mix_FreeChunk(doom->sound[i].sound);
	return (1);
}
