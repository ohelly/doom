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

t_sound	*add_sound(t_doom *doom, char *name, int index, int volume)
{
	t_sound *s;

	s = &doom->sound[index];
	s->sound = Mix_LoadWAV(name);
	s->volume = volume;
	ft_strdel(&name);
	return (s);
}

int		load_music(t_doom *doom)
{
	t_music *m;
	t_sound *s;
	char	*env;
	char	*tmp;

	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	m = &doom->music[0];
	tmp = ft_strjoin(env, "/music.mp3");
	m->music = Mix_LoadMUS(tmp);
	m->volume = 0;
	ft_strdel(&tmp);

	tmp = ft_strjoin(env, "/hit.wav");
	add_sound(doom, tmp, SOUND_SHOOT, 100);
	tmp = ft_strjoin(env, "/pickup.wav");
	add_sound(doom, tmp, SOUND_PICKUP, 100);
	tmp = ft_strjoin(env, "/weapon_pick.wav");
	add_sound(doom, tmp, SOUND_WEAPON_PICKUP, 100);
	tmp = ft_strjoin(env, "/death.wav");
	add_sound(doom, tmp, SOUND_DEATH, 100);
	tmp = ft_strjoin(env, "/interact.wav");
	add_sound(doom, tmp, SOUND_INTERACT, 100);
	tmp = ft_strjoin(env, "/enemy_attack.wav");
	add_sound(doom, tmp, SOUND_E_ATTACK, 100);
	tmp = ft_strjoin(env, "/lost.wav");
	add_sound(doom, tmp, SOUND_LOSS, 100);
	tmp = ft_strjoin(env, "/reload.wav");
	add_sound(doom, tmp, SOUND_RELOAD, 100);
	tmp = ft_strjoin(env, "/scream.wav");
	add_sound(doom, tmp, SOUND_SCREAM, 100);
	tmp = ft_strjoin(env, "/jump.wav");
	add_sound(doom, tmp, SOUND_JUMP, 100);
	tmp = ft_strjoin(env, "/damage.wav");
	add_sound(doom, tmp, SOUND_DAMAGE, 100);
	tmp = ft_strjoin(env, "/pistol.wav");
	add_sound(doom, tmp, SOUND_PISTOL, 100);
	tmp = ft_strjoin(env, "/shotgun.wav");
	add_sound(doom, tmp, SOUND_SHOTGUN, 100);
	tmp = ft_strjoin(env, "/ripper.wav");
	add_sound(doom, tmp, SOUND_RIPPER, 60);
	tmp = ft_strjoin(env, "/foot.wav");
	add_sound(doom, tmp, SOUND_FOOT, 100);
	tmp = ft_strjoin(env, "/explosion.wav");
	add_sound(doom, tmp, SOUND_EXPLOSIVE, 100);
	tmp = ft_strjoin(env, "/crash.wav");
	add_sound(doom, tmp, SOUND_CRASH, 100);
	free(env);
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
