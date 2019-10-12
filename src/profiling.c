#include "doom.h"

int		profile_output(t_doom *doom)
{
	printf("===Profiling results===\n");
	printf("Frametime: %f ms\n", doom->time_frame);
	printf("FPS is %f\n", 1 / doom->time_frame);
	printf("Average FPS is %f\n", 1 / (doom->time_fps_total / doom->time_fps_count));
	doom->time_fps_count = 0;
	doom->time_fps_total = 0;
	//printf("player.where is %f:%f\n", doom->player.where.x, doom->player.where.y);
	//это все пока не работает
	//printf("Sprites drawtime: %f ms\n", (doom->times[2] - doom->times[3]) / 1000);
	//printf("Walls drawtime: %f ms\n", (doom->times[4] - doom->times[5]) / 1000);
	//printf("random drawtime: %f ms\n", (doom->times[6] - doom->times[7]));
	printf("===Profiling completed===\n");
	return (1);
}