#include "doom.h"

int		load_music(t_doom *doom)
{
	t_music *m;
	t_sound *s;

	m = &doom->music[0];
	m->music = Mix_LoadMUS("./music.mp3");
	m->volume = 10;

	s = &doom->sound[0];
	s->sound = Mix_LoadWAV("hit.wav");
	s->volume = 128;

	s = &doom->sound[1];
	s->sound = Mix_LoadWAV("pickup.wav");
	s->volume = 128;

	s = &doom->sound[2];
	s->sound = Mix_LoadWAV("death.wav");
	s->volume = 128;
	printf("Music loaded!\n");
}

int		play_sound(t_doom *doom, int index)
{
	Mix_Chunk	*sound;
	int			ch;

	if (index >= 10 || index < 0)
		return (0);
	printf("Playing sound with %d index, %d volume\n", index, doom->sound[index].volume);
	sound = doom->sound[index].sound;
	ch = Mix_PlayChannel(-1, sound, 0);
	Mix_Volume(ch, doom->sound[index].volume);
	return (1);
}

int		play_music(t_doom *doom, int index)
{
	Mix_Music *music;

	if (index >= 2 || index < 0)
		return(0);
	printf("Playing music with %d index, %d volume\n", index, doom->music[index].volume);
	music = doom->music[index].music;
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(doom->music[index].volume);
}

int		sound_free_everything(t_doom *doom)
{
	int i;

	i = 0;
	while (i < 2)
	{
		Mix_FreeMusic(doom->music[i].music);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		Mix_FreeChunk(doom->sound[i].sound);
		i++;
	}
}