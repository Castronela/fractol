/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:27:06 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 16:53:24 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_data	fractal;

	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)) || (!ft_strncmp(av[1],
				"julia", 5) && ac == 4))
	{
		fractal.frctl_type = av[1];
		fractal.ptr = mlx_init();
		if (!fractal.ptr)
			clean(&fractal, 1);
		data_init(&fractal);
		if (!ft_strncmp(av[1], "julia", 5))
		{
			if (!valid_input(av[2], fractal) || !valid_input(av[3], fractal))
				return (print_err(), 1);
			fractal.is_julia = 1;
			fractal.julia.x = dbl_atoi(av[2]);
			fractal.julia.y = dbl_atoi(av[3]);
		}
		instructions();
		build_img(&fractal);
		hooks(&fractal);
		mlx_loop(fractal.ptr);
		return (0);
	}
	return (print_err(), 1);
}
