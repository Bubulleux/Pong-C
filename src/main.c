#include "h/define.h"

#include <sys/time.h>

long long current_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}



int update(t_vars *vars)
{
	vars->frame += 1;

	if (vars->time->last_time_value == 0)
		vars->time->last_time_value = current_timestamp();
	
	vars->time->delta_time = (current_timestamp() - vars->time->last_time_value) / 1000.0;
	
	// printf("\r");
	// for (int i = 0; i < 4; i++)
	// {
	// 	printf("%d ", vars->input_vars->inputs_pressed[i][1]);
	// }
	if (vars->time->delta_time >= (1.0 / FPS))
	{
		vars->time->last_time_value = current_timestamp();
		update_object(vars);
		render(vars);

		fflush(stdout);
	}
}


int main(void)
{
	t_vars vars;

	vars.frame = 0;
	vars.mlx = mlx_init();

	init_renderer(&vars);
	init_objects(&vars);
	init_input(&vars);

	vars.time = malloc(sizeof(t_time));

	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
}