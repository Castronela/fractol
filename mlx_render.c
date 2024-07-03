/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:57:21 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 16:28:41 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_fractal(t_data *fractal)
{
	double		iter;
	t_complex	a;

	fractal->c.x = -1;
	while (++fractal->c.x < WIDTH)
	{
		fractal->c.y = -1;
		while (++fractal->c.y < HEIGHT)
		{
			a.x = l_interp(fractal->c.x, -2.0 * fractal->zoom, 2.0
					* fractal->zoom, WIDTH) + fractal->shift.x;
			a.y = l_interp(fractal->c.y, 2.0 * fractal->zoom, -2.0
					* fractal->zoom, HEIGHT) + fractal->shift.y;
			iter = is_in_set(&a, fractal);
			if (iter < fractal->iters)
				my_pixel_put(&fractal->img, fractal->c.x, fractal->c.y,
					set_color(iter, fractal));
			else
				my_pixel_put(&fractal->img, fractal->c.x, fractal->c.y,
					COLOR_WHITE);
		}
	}
	mlx_put_image_to_window(fractal->ptr, fractal->win, fractal->img.img_addr,
		0, 0);
	return (0);
}

void	data_init(t_data *fractal)
{
	fractal->num.sign_count = 0;
	fractal->num.dec_sep_count = 0;
	fractal->num.len = 0;
	fractal->is_julia = 0;
	fractal->iters = 50;
	fractal->zoom = 1;
	fractal->shift.x = 0;
	fractal->shift.y = 0;
	fractal->color_scheme = 1;
}

int	build_img(t_data *fractal)
{
	fractal->win = mlx_new_window(fractal->ptr, WIDTH, HEIGHT,
			fractal->frctl_type);
	if (!fractal->win)
		clean(fractal, 1);
	fractal->img.img_addr = mlx_new_image(fractal->ptr, WIDTH, HEIGHT);
	if (!fractal->img.img_addr)
		clean(fractal, 1);
	fractal->img.pixel_addr = mlx_get_data_addr(fractal->img.img_addr,
			&fractal->img.bpp, &fractal->img.size_line, &fractal->img.endian);
	if (!fractal->img.pixel_addr)
		clean(fractal, 1);
	render_fractal(fractal);
	return (1);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixel_addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clean(t_data *fractal, int error)
{
	if (fractal->img.img_addr)
		mlx_destroy_image(fractal->ptr, fractal->img.img_addr);
	if (fractal->win)
		mlx_destroy_window(fractal->ptr, fractal->win);
	if (fractal->ptr)
	{
		free(fractal->ptr);
		fractal->ptr = NULL;
	}
	if (error)
	{
		write(1, "MLX Error\n", 10);
		exit(1);
	}
	exit(error);
}
