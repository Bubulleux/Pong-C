#include "h/define.h"

int ball_vel_x = 0;
int ball_vel_y = 0;

int ply_score = 0;
int ia_score = 0;

void init_objects(t_vars *vars)
{
	vars->objects = (t_objects*) malloc(sizeof(t_objects));
	vars->objects->background = make_square(0, 0, vars->win_width, vars->win_height, 0x00111111);
	
	srand(time(NULL));
	create_obj(vars);
}

void create_obj(t_vars *vars)
{
	vars->objects->player = make_square(20, 220, 10, 60, 0x00ffffff);
	vars->objects->ia = make_square(970, 220, 10, 60, 0x00ffffff);
	vars->objects->ball = make_square(495, 245, 10, 10, 0x00cccccc);

	ball_vel_x = -2;
	ball_vel_y = (rand() % 3 + 1) * (rand() % 2 == 0 ? -1 : 1);
	printf("%d %d\n", ball_vel_x, ball_vel_y);
}

void update_object(t_vars *vars)
{
	set_player_pose(vars);
	if (IA_HARD)
		set_ia_pose_hard(vars);
	else
		set_ia_pose(vars);
	update_ball(vars);
}

void set_player_pose(t_vars *vars)
{

	int x = 0;
	int y = 0;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);

	if (abs((y - 30) - vars->objects->player->pos_y) < SPEED)
		vars->objects->player->pos_y = (y - 25);
	
	if ((y - 30) != vars->objects->player->pos_y)
		vars->objects->player->pos_y += (y - 25) > vars->objects->player->pos_y ?  SPEED : -SPEED;
}

void set_ia_pose(t_vars *vars)
{
	int y = vars->objects->ball->pos_y;
	if (abs((y - 25) - vars->objects->ia->pos_y) < SPEED)
		vars->objects->ia->pos_y = (y - 25);
	
	if ((y - 25) != vars->objects->ia->pos_y)
		vars->objects->ia->pos_y += (y - 25) > vars->objects->ia->pos_y ?  SPEED : -SPEED;
}

void set_ia_pose_hard(t_vars *vars)
{
	int *ball_x = &vars->objects->ball->pos_x;
	int *ball_y = &vars->objects->ball->pos_y;

	int dist = ball_vel_x < 0 ? (*ball_x - 30) + 940 : 970 - *ball_x;
	int unity = abs(dist / ball_vel_x);
	int y = *ball_y;
	int vel_y = ball_vel_y;
	for(int i = 0; i < unity; i += 1)
	{
		if (y + ball_vel_y < 0 || y + 10 + ball_vel_y >= 500)
			vel_y = -vel_y;
		y += vel_y;
	}
	
	if (abs((y - 25) - vars->objects->ia->pos_y) < SPEED)
		vars->objects->ia->pos_y = (y - 25);
	
	if ((y - 25) != vars->objects->ia->pos_y)
		vars->objects->ia->pos_y += (y - 25) > vars->objects->ia->pos_y ?  SPEED : -SPEED;
}


void update_ball(t_vars *vars)
{
	int *x_ball = &(vars->objects->ball->pos_x);
	int *y_ball = &(vars->objects->ball->pos_y);

	if (*x_ball + ball_vel_x < 30 || *x_ball + 10 + ball_vel_x >= 970)
	{
		if (*x_ball + ball_vel_x < 30 && (*y_ball + 10 < vars->objects->player->pos_y || *y_ball > vars->objects->player->pos_y + 60) && !GOD)
		{
			ia_score += 1;
			round_over(vars);
			return;
		}
		if (*x_ball + ball_vel_x + 10 >= 970 && (*y_ball + 10 < vars->objects->ia->pos_y || *y_ball > vars->objects->ia->pos_y + 60))
		{
			ply_score += 1;
			round_over(vars);
			return;
		}

		ball_vel_x = -ball_vel_x;

		if (rand() % 3 == 0)
		{
			ball_vel_x += ball_vel_x > 0 ? 1 : -1;
			ball_vel_y += ball_vel_y > 0 ? 1 : -1;
		}
	}
	if (*y_ball + ball_vel_y < 0 || *y_ball + 10 + ball_vel_y >= 500)
	{
		ball_vel_y = -ball_vel_y;
		if (rand() % 2 == 0)
			ball_vel_y += rand() % 3 - 1;
	}
	
	*x_ball += ball_vel_x;
	*y_ball += ball_vel_y;
}

void round_over(t_vars *vars)
{
	free(vars->objects->ia);
	free(vars->objects->player);
	free(vars->objects->ball);
	printf("\n%d-%d\n", ply_score, ia_score);
	create_obj(vars);
}

t_square* make_square(int pos_x, int pos_y, int size_x, int size_y, int color)
{
	t_square* square = (t_square*) malloc(sizeof(t_square));
	square->pos_x = pos_x; 
	square->pos_y = pos_y;
	square->size_x = size_x;
	square->size_y = size_y;
	square->color = color;
	return square;
}


bool is_collide(t_square *square_a, t_square *square_b)
{
	// printf("%d ", square_a->pos_x > (square_b->pos_x + square_b->size_x));
	// printf("%d ", (square_a->pos_x + square_a->size_x) < square_b->pos_x);
	// printf("%d ", square_a->pos_y > (square_b->pos_y + square_b->size_y));
	// printf("%d ", (square_a->pos_y + square_a->size_y) < square_b->pos_y);
	// printf("\n");

	if (square_a->pos_x > (square_b->pos_x + square_b->size_x) ||
		(square_a->pos_x + square_a->size_x) < square_b->pos_x ||
		square_a->pos_y > (square_b->pos_y + square_b->size_y) ||
		(square_a->pos_y + square_a->size_y) < square_b->pos_y)

		return false;
	else
		return true;
}

bool is_collide_point(t_square *square, int x, int y)
{
	if ((x < square->pos_x || x > square->pos_x + square->size_x) ||
		(y < square->pos_y || y > square->pos_y + square->size_y))
		
		return false;
	else
	{
		//printf("x: %d, y: %d, square: %d %d %d %d\n", x, y, square->pos_x, square->pos_y, square->size_x, square->size_y);
		return true;
	}
}

