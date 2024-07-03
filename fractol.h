/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:21:18 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 16:53:49 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 1000
# define ZOOM_FACTOR 1.05
# define SHIFT_FACTOR 0.15

/** Color definitions **/
# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xffffff

/** Color spectrum definitions **/
# define MULTICOLOR 1
# define BLUE_RED 2
# define BLUE_WHITE 3
# define BLACK_WHITE 4
# define DBLUE_BROWN 5

/** Key definitions **/
# define KEY_ESC 53
# define KEY_PRESS 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define DESTROY_NOTIFY 17
# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define KEY_NUM_ONE 18
# define KEY_NUM_TWO 19
# define KEY_NUM_THREE 20
# define KEY_NUM_FOUR 21
# define KEY_NUM_FIVE 23
# define KEY_PLUS 69
# define KEY_MINUS 78

typedef struct s_numinfo
{
	int			sign_count;
	int			dec_sep_count;
	int			len;
}				t_numinfo;

typedef struct s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef struct s_img
{
	void		*img_addr;
	char		*pixel_addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_data
{
	char		*frctl_type;
	void		*ptr;
	void		*win;
	t_img		img;
	t_complex	c;
	double		iters;
	double		zoom;
	t_complex	shift;
	int			is_julia;
	t_complex	julia;
	int			color_scheme;
	t_numinfo	num;
}				t_data;

/** Main **/
int				main(int ac, char **av);

/** Handle Error **/
void			clean(t_data *fractal, int error);

/** Render **/
void			data_init(t_data *fractal);
int				build_img(t_data *fractal);
int				render_fractal(t_data *fractal);
void			my_pixel_put(t_img *img, int x, int y, int color);

/** Color **/
int				set_rgb(int r, int g, int b);
int				set_color(double iter, t_data *fractal);

/** Complex Math **/
double			is_in_set(t_complex *a, t_data *fractal);
void			c_square(t_complex *z);
double			hypotenuse(t_complex z);
double			l_interp(double num, double min, double max, int c);

/** Handle Hook **/
int				key_hook(int keycode, t_data *fractal);
int				exit_hook(t_data *fractal);
int				mouse_hook(int keycode, int x, int y, t_data *fractal);
void			hooks(t_data *fractal);

/** Utils **/
void			print_err(void);
int				ft_strncmp(char *s1, char *s2, int n);
int				valid_input(char *str, t_data fractal);
double			dbl_atoi(char *str);
void			instructions(void);

#endif