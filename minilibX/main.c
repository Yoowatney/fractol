#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mlx.h"

#define SUCCESS 1
#define ERROR  -1
#define WIDTH  800
#define ITER_MAX 200
#define HEIGHT 700
#define MANDEL 77
#define JULIA  74
#define BURN   102
#define M_COLOR	11
#define J_COLOR	12
#define B_COLOR 13

typedef struct s_data
{
	void 	*img_ptr;
	char	*addr;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	int	type;
	int color;
	double	start_x;
	double	start_y;
	double	zoom;
	double	constant[2];
	int	(*color_func)(int);
}		t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
}				t_mlx;

void	check_set(char *set, t_data *img)
{
	if (strcmp(set, "Mandelbrot") == 0)
	{
		img->type = MANDEL;
		img->color = M_COLOR;
		return ;
	}
	else if (strcmp(set, "Julia") == 0)
	{
		img->type = JULIA;
		img->color = J_COLOR;
		return ;
	}
	else if (strcmp(set, "Burning Ship") == 0)
	{
		img->type = BURN;
		img->color = B_COLOR;
		return ;
	}
	/*else if (strcmp(set, "") == 0)*/
	printf("Usage : %s 'Mandelbrot' or 'Julia' or 'Burning ship'\n", "./fractol");
	exit(0);
}

int	init(t_mlx	*mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (ERROR);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "fractol");
	if (mlx->win_ptr == NULL)
		return (ERROR);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (mlx->img.img_ptr == NULL)
		return (ERROR);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bits_per_pixel, &mlx->img.size_line, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (ERROR);
	mlx->img.zoom = 4.0;
	mlx->img.start_x = -2.0;
	mlx->img.start_y = -2.0;
	return (SUCCESS);
}



void	my_mlx_pixel_put(t_data	*img, int x, int y, int color)
{
	unsigned char *dest;
	dest = (unsigned char *)img->addr + x * (img->bits_per_pixel / 8) + y * (img->size_line);
	*(unsigned int *)dest = color;
}

/*fractol set*/

int	julia(double x, double y, int iter, t_data *image)
{
	double x_new, c_re, c_im;

	c_re = image->constant[0], c_im = image->constant[1];
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		iter++;
	}
	return (iter);
}

int	mandelbrot(double c_re, double c_im, int iter)
{
	double x, y, x_new;

	x = 0;
	y = 0;
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		iter++;
	}
	return (iter);
}

int	burningship(double c_re, double c_im, int iter)
{
	double x, y, x_new;

	x = 0;
	y = 0;
	while (pow(x, 2.0) + pow(x, 2.0) < 4.0 && iter < ITER_MAX)
	{
		x_new = pow(x, 2.0) - pow(y, 2.0) + c_re;
		y = 2 * x * y + c_im;
		if (y < 0)
			y *= -1;
		x = x_new;
		iter++;
	}
	return (iter);
}

/*color set about each fractol*/

int		color_mandel(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.5) + 32;
	g = log((double)iter * 0.7);
	b = log((double)iter * 0.9);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
	return (color);
}

int		color_julia(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.7) + 32;
	g = log((double)iter * 0.85);
	b = log((double)iter * 0.5);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
	return (color);
}

int		color_burn(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = log((double)iter * 0.9) + 32;
	g = log((double)iter * 0.5);
	b = log((double)iter * 0.7);
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
	return (color);
}

/*initialization*/

void	assign_func(t_data *image)
{
	if (image->color == M_COLOR)
		image->color_func = &color_mandel;
	else if (image->color == J_COLOR)
		image->color_func = &color_julia;
	else if (image->color == B_COLOR)
		image->color_func = &color_burn;
}

void	assign_color(t_data *img)
{
	if (img->color == M_COLOR)
		img->color = J_COLOR;
	else if (img->color == J_COLOR)
		img->color = B_COLOR;
	else if (img->color == B_COLOR)
		img->color = M_COLOR;
	assign_func(img);
}

/*put pixel*/

void	put_pixel(t_data *img, double c_re, double c_im)
{
	int	x, y, iter;
	double dx, dy, temp;

	temp = c_re, y= -1;
	dx = img->zoom / WIDTH, dy = img->zoom / HEIGHT;
	while (++y < HEIGHT)
	{
		x = -1;
		c_re = temp;
		while (++x < WIDTH)
		{
			if (img->type == MANDEL)
				iter = mandelbrot(c_re, c_im, 0);
			else if (img->type == JULIA)
				iter = julia(c_re, c_im, 0, img);
			else
				iter = burningship(c_re, c_im, 0);
			if (iter < ITER_MAX)
				my_mlx_pixel_put(img, x, y, img->color_func(iter));
			else
			    my_mlx_pixel_put(img, x, y, 0x00000000);
			c_re += dx;
		}
		c_im += dy;
	}
}

/*control event*/

int key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
	if (keycode == 123)
		mlx->img.start_x -= (0.25) * mlx->img.zoom;
	else if (keycode == 124)
		mlx->img.start_x += (0.25) * mlx->img.zoom;
	else if (keycode == 125)
		mlx->img.start_y += (0.25) * mlx->img.zoom;
	else if (keycode == 126)
		mlx->img.start_y -= (0.25) * mlx->img.zoom;
	put_pixel(&mlx->img, mlx->img.start_x, mlx->img.start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

int zoom(int button, int x, int y, t_mlx *mlx)
{
	double new_x, new_y;
	t_data	*image;
	image = &mlx->img;

	if (button == 5)
	{
		new_x = (image->zoom) * (double)x / WIDTH + image->start_x;
		new_y = (image->zoom) * (double)y / HEIGHT + image->start_y;
		image->start_x = new_x - (image->zoom) * 0.5;
		image->start_y = new_y - (image->zoom) * 0.5;
		image->zoom *= 0.65;
	}
	else if (button == 4)
	{
		new_x = (image->zoom) * (double)x / WIDTH + image->start_x;
		new_y = (image->zoom) * (double)y / WIDTH + image->start_y;
		image->start_x = new_x - (image->zoom / 2);
		image->start_y = new_y - (image->zoom / 2);
		image->zoom /= 0.65;
    }
	put_pixel(image, image->start_x, image->start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, image->img_ptr, 0, 0);
	return (0);
}

int	julia_event(int x, int y, t_mlx *mlx)
{
	t_data *image;

	image = &mlx->img;
	(image->constant)[0] = (image->zoom) * (double)x / WIDTH + image->start_x;
	(image->constant)[1] = (image->zoom) * (double)y / HEIGHT + image->start_y;
	put_pixel(image, image->start_x, image->start_y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, image->img_ptr, 0, 0);
	return (0);
}

int	color_shift(int keycode, t_mlx *mlx)
{
	if (keycode == 258)
	{
		if (mlx->img.color == M_COLOR)
			mlx->img.color = J_COLOR;
		else if (mlx->img.color == J_COLOR)
			mlx->img.color = B_COLOR;
		else if (mlx->img.color == B_COLOR)
			mlx->img.color = M_COLOR;
		assign_color(&mlx->img);
		put_pixel(&mlx->img, mlx->img.start_x, mlx->img.start_y);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	}
	return (SUCCESS);
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc != 2)
	{
		printf("Usage : %s 'Mandelbrot' or 'Julia' or 'Burning Ship'\n", argv[0]);
		return (0);
	}
	check_set(argv[1], &mlx.img);
	init(&mlx);
	assign_func(&mlx.img);
	put_pixel(&mlx.img, -2.0, -2.0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, &key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 6, 0, &julia_event, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, &color_shift, &mlx);
	mlx_mouse_hook(mlx.win_ptr, &zoom, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
