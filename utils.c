/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstinghe <dstinghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:59:01 by dstinghe          #+#    #+#             */
/*   Updated: 2024/06/10 17:16:07 by dstinghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	instructions(void)
{
	write(1, "Actions:\n", 10);
	write(1, "\tuse ARROW KEYS to pan\n", 24);
	write(1, "\tuse MOUSE SCROLL to zoom\n", 27);
	write(1, "\tuse KEYS 1 - 5 to change color spectrum\n", 42);
	write(1, "\tuse KEYPAD PLUS and MINUS to change fractal depth\n", 52);
	write(1, "\tuse ESC to exit\n", 18);
}

void	print_err(void)
{
	write(1, "Invalid input!\n", 16);
	write(1, "Valid input:\n\n\t\'mandelbrot\'", 28);
	write(1, "\tOR\t\'julia\' ", 13);
	write(1, "\'integer.decimal/s\' \'integer.decimal/s\'\n", 41);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n)
	{
		s1++;
		s2++;
		n--;
	}
	return (*s1 - *s2);
}

double	dbl_atoi(char *str)
{
	double	fraction;
	double	whole;
	double	sign;

	whole = 0;
	fraction = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -sign;
	}
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		fraction *= 0.1;
		if (*str >= '0' && *str <= '9')
			whole = whole * 10 + (*str - '0');
		if (*str++ == '.')
			fraction = 1;
	}
	if (fraction == 0)
		fraction = 1;
	return (whole * sign * fraction);
}

int	valid_input(char *str, t_data fractal)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && (*str < 9 || *str > 13) && *str != '-'
			&& *str != '+' && *str != '.' && *str != ' ')
			return (0);
		if (*str >= '0' && *str <= '9')
			fractal.num.len++;
		if (*str == '.')
			fractal.num.dec_sep_count++;
		if (*str == '-' || *str == '+')
			fractal.num.sign_count++;
		if ((*str < '0' || *str > '9') && *str != '.' && str[1]
			&& (str[1] >= '0' && str[1] <= '9') && fractal.num.len)
			return (0);
		if ((*str == '-' || *str == '+') && str[1] && (str[1] < '0'
				|| str[1] > '9'))
			return (0);
		str++;
	}
	if (fractal.num.len == 0 || fractal.num.len > 15
		|| fractal.num.sign_count > 1 || fractal.num.dec_sep_count > 1)
		return (0);
	return (1);
}
