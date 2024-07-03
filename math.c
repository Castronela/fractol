/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:58:29 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:47 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	c_square(t_complex *z)
{
	double	temp;

	temp = z->x;
	z->x = (z->x * z->x) - (z->y * z->y);
	z->y = 2 * temp * z->y;
}

double	hypotenuse(t_complex z)
{
	return (sqrt((z.x * z.x) + (z.y * z.y)));
}

double	is_in_set(t_complex *a, t_data *fractal)
{
	t_complex	z;
	int			i;

	i = 0;
	z.x = 0;
	z.y = 0;
	if (fractal->is_julia)
	{
		z.x = a->x;
		z.y = a->y;
	}
	else
	{
		fractal->julia.x = a->x;
		fractal->julia.y = a->y;
	}
	while (i < fractal->iters && hypotenuse(z) < 2.0)
	{
		c_square(&z);
		z.x += fractal->julia.x;
		z.y += fractal->julia.y;
		i++;
	}
	return (i);
}

double	l_interp(double num, double min, double max, int c)
{
	return ((num - 0) * (max - min) / (double)c + min);
}
