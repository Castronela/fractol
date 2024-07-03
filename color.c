/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:55:55 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 16:29:41 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	set_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	set_color(double iter, t_data *fractal)
{
	double	color_id;

	color_id = l_interp(iter, 0, 255, fractal->iters);
	if (fractal->color_scheme == MULTICOLOR)
		return (l_interp(iter, set_rgb(0, 0, 0), set_rgb(255, 255, 255),
				fractal->iters));
	else if (fractal->color_scheme == BLUE_RED)
		return (set_rgb(fabs(10 - color_id), fabs(50 - color_id), fabs(150
					- color_id)));
	else if (fractal->color_scheme == BLUE_WHITE)
		return (set_rgb(fabs(10 - color_id), fabs(50 - color_id), color_id
				+ 100));
	else if (fractal->color_scheme == BLACK_WHITE)
		return (set_rgb(color_id, color_id, color_id));
	else if (fractal->color_scheme == DBLUE_BROWN)
		return (set_rgb(color_id, fabs(color_id - 25), fabs(color_id - 50)));
	return (1);
}
