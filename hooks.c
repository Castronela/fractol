/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:56:27 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 15:56:29 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_data *fractal)
{
	if (keycode == KEY_ESC)
		clean(fractal, 0);
	else if (keycode == KEY_NUM_ONE)
		fractal->color_scheme = MULTICOLOR;
	else if (keycode == KEY_NUM_TWO)
		fractal->color_scheme = BLUE_RED;
	else if (keycode == KEY_NUM_THREE)
		fractal->color_scheme = BLUE_WHITE;
	else if (keycode == KEY_NUM_FOUR)
		fractal->color_scheme = BLACK_WHITE;
	else if (keycode == KEY_NUM_FIVE)
		fractal->color_scheme = DBLUE_BROWN;
	else if (keycode == KEY_UP)
		fractal->shift.y += fractal->zoom * SHIFT_FACTOR;
	else if (keycode == KEY_DOWN)
		fractal->shift.y -= fractal->zoom * SHIFT_FACTOR;
	else if (keycode == KEY_LEFT)
		fractal->shift.x -= fractal->zoom * SHIFT_FACTOR;
	else if (keycode == KEY_RIGHT)
		fractal->shift.x += fractal->zoom * SHIFT_FACTOR;
	else if (keycode == KEY_PLUS)
		fractal->iters *= 1.1;
	else if (keycode == KEY_MINUS)
		fractal->iters /= 1.1;
	return (render_fractal(fractal));
}

int	mouse_hook(int keycode, int x, int y, t_data *fractal)
{
	(void)x;
	(void)y;
	if (keycode == MOUSE_UP)
		fractal->zoom *= ZOOM_FACTOR;
	else if (keycode == MOUSE_DOWN)
		fractal->zoom /= ZOOM_FACTOR;
	render_fractal(fractal);
	return (0);
}

int	exit_hook(t_data *fractal)
{
	clean(fractal, 0);
	return (0);
}

void	hooks(t_data *fractal)
{
	mlx_hook(fractal->win, KEY_PRESS, 0, key_hook, fractal);
	mlx_hook(fractal->win, DESTROY_NOTIFY, 0, exit_hook, fractal);
	mlx_hook(fractal->win, MOUSE_DOWN, 0, mouse_hook, fractal);
	mlx_hook(fractal->win, MOUSE_UP, 0, mouse_hook, fractal);
}
