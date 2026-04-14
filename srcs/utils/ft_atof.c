/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:10:05 by fbenini-          #+#    #+#             */
/*   Updated: 2026/04/14 18:10:15 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

static int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static double	parse_fraction(const char *str, int *i)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (isdigit(str[*i]))
		{
			fraction = fraction * 10.0 + (str[*i] - '0');
			divisor *= 10.0;
			(*i)++;
		}
	}
	return (fraction / divisor);
}

static double	parse_number(const char *str, int *i)
{
	double	result;

	result = 0.0;
	while (isdigit(str[*i]))
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	sign = 1;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = parse_number(str, &i);
	result += parse_fraction(str, &i);
	return (result * sign);
}
