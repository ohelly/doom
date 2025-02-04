/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:21:32 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 01:33:13 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_sound(t_sound *s, char *env, char *str, int volume)
{
	char	*tmp;

	tmp = ft_strjoin(env, str);
	s->sound = Mix_LoadWAV(tmp);
	s->volume = volume;
	ft_strdel(&tmp);
}

void	load_sound_music(t_music *m, char *env, char *str, int volume)
{
	char	*tmp;

	tmp = ft_strjoin(env, str);
	m->music = Mix_LoadMUS(tmp);
	ft_strdel(&tmp);
	m->volume = volume;
}

void	load_music(t_doom *doom)
{
	char	*env;

	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	load_sound_music(&doom->music[0], env, "/music.mp3", 30);
	load_sound(&doom->sound[SOUND_SHOOT], env, "/hit.wav", 100);
	load_sound(&doom->sound[SOUND_PICKUP], env, "/pickup.wav", 100);
	load_sound(&doom->sound[SOUND_WEAPON_PICKUP], env, "/weapon_pick.wav", 100);
	load_sound(&doom->sound[SOUND_DEATH], env, "/death.wav", 100);
	load_sound(&doom->sound[SOUND_INTERACT], env, "/interact.wav", 100);
	load_sound(&doom->sound[SOUND_E_ATTACK], env, "/enemy_attack.wav", 100);
	load_sound(&doom->sound[SOUND_LOSS], env, "/lost.wav", 100);
	load_sound(&doom->sound[SOUND_RELOAD], env, "/reload.wav", 100);
	load_sound(&doom->sound[SOUND_SCREAM], env, "/scream.wav", 100);
	load_sound(&doom->sound[SOUND_JUMP], env, "/jump.wav", 100);
	load_sound(&doom->sound[SOUND_DAMAGE], env, "/damage.wav", 100);
	load_sound(&doom->sound[SOUND_PISTOL], env, "/pistol.wav", 100);
	load_sound(&doom->sound[SOUND_SHOTGUN], env, "/shotgun.wav", 100);
	load_sound(&doom->sound[SOUND_RIPPER], env, "/ripper.wav", 70);
	load_sound(&doom->sound[SOUND_FOOT], env, "/foot.wav", 100);
	load_sound(&doom->sound[SOUND_EXPLOSIVE], env, "/explosion.wav", 100);
	load_sound(&doom->sound[SOUND_CRASH], env, "/crash.wav", 100);
	ft_strdel(&env);
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
	return (1);
}
