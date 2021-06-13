#include "h/define.h"

void init_renderer(t_vars *vars)
{
	vars->win_width = 1000;
	vars->win_height = 500;
	
	vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height, "2D Game 2");

}

void render(t_vars *vars)
{
	t_img *img;
	img = (t_img*) malloc(sizeof(t_img));
	img->img = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel, &img->line_lenght, &img->endian);
	
	render_square(vars, vars->objects->background, img);
	render_square(vars, vars->objects->ia, img);
	render_square(vars, vars->objects->ball, img);
	render_square(vars, vars->objects->player, img);

	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	mlx_destroy_image(vars->mlx, img->img);
	free(img);
	
}

void render_square(t_vars *vars, t_square *square, t_img *img)
{
	for (int y = 0; y <= square->size_y; y++)
	{
		for (int x = 0; x <= square->size_x; x++)
		{
			if (is_collide_point(vars->objects->background, square->pos_x + x, square->pos_y + y))
				set_pixel(img, square->pos_x + x, square->pos_y + y, square->color);
		}
	}
}

void set_pixel(t_img *img, int x, int y, int color)
{
	char **dst;
	dst = (char**) malloc(sizeof(char*));
	*dst = img->addr + (y * img->line_lenght + x * (img->bit_per_pixel / 8));
	*(unsigned int*)*dst = color;
	free(dst);
}