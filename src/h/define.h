#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include <inttypes.h>
#include <math.h>

//------------Const------------
//Inpute
#define UP_ARROW 65362
#define DOWN_ARROW 65364

#define FPS 60.0

#define SPEED 10

#define IA_HARD false
#define GOD false

//------------Struct------------
typedef struct s_img
{
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_lenght;
	int endian;
} t_img;

typedef struct s_square
{
	int pos_x;
	int pos_y;
	int size_x;
	int size_y;
	int color;
} t_square;

typedef struct s_objects
{
	t_square *player;
	t_square *ia;
	t_square *ball;
	t_square *background;
} t_objects;

typedef struct s_input_vars
{
	bool up_pressed;
	bool down_pressed;
} t_input_vars;

typedef struct s_time
{
	float delta_time;
	long last_time_value;
} t_time;

typedef struct s_vars 
{
	void *mlx;
	void *win;
	unsigned int win_width;
	unsigned int win_height;
	unsigned int frame;

	t_objects *objects;
	t_input_vars *input_vars;
	t_time *time;
} t_vars;




//------------Function------------

//main.c
long long current_timestamp();
int update(t_vars *vars);
void maint(void);

//object.c
void init_objects(t_vars *vars);
void create_obj(t_vars *vars);
void update_object(t_vars *vars);
void set_player_pose(t_vars *vars);
void set_ia_pose(t_vars *vars);
void set_ia_pose_hard(t_vars *vars);
void update_ball(t_vars *vars);
void round_over(t_vars *vars);
t_square* make_square(int pos_x, int pos_y, int size_x, int size_y, int color);
bool is_collide(t_square *square_a, t_square *square_b);
bool is_collide_point(t_square* square, int x, int y);

//renderer.c
void init_renderer(t_vars *vars);
void render(t_vars *vars);
void render_square(t_vars *vars, t_square *square, t_img *img);
void set_pixel(t_img *img, int x, int y, int color);

//input.c
int key_pressed(int keycode, t_vars *vars);
int key_released(int keycode, t_vars *vars);
void init_input(t_vars *vars);



