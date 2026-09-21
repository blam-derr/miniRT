/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric_token_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:49:16 by fbenini-          #+#    #+#             */
/*   Updated: 2026/09/21 13:49:25 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils_bonus.h"

int	is_numeric_token(char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			has_digit = 1;
		else if (s[i] != '.' && s[i] != 'e' && s[i] != 'E'
			&& s[i] != '-' && s[i] != '+')
			return (0);
		i++;
	}
	return (has_digit);
}
