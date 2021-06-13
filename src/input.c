#include "h/define.h"

int key_pressed(int keycode, t_vars *vars)
{
	if (keycode == UP_ARROW)
	{
		vars->input_vars->up_pressed = true;
	}
	else if (keycode == DOWN_ARROW)
		vars->input_vars->down_pressed = true;
}

int key_released(int keycode, t_vars *vars)
{
	if (keycode == UP_ARROW)
	{
		vars->input_vars->up_pressed = false;
	}
	else if (keycode == DOWN_ARROW)
		vars->input_vars->down_pressed = false;
}


void init_input(t_vars *vars)
{
    mlx_hook(vars->win, 2, 1L<<0, key_pressed, vars);
	mlx_hook(vars->win, 3, 1L<<1, key_released, vars);
	vars->input_vars = malloc(sizeof(t_input_vars));
}