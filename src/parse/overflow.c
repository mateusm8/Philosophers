/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:17:20 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/12 16:52:06 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_overflow_int(char *str)
{
	int				i;
	unsigned int	acc;
	unsigned int	nb;

	i = 0;
	acc = 0;
	while (str[i])
	{
		nb = str[i] - 48;
		if (acc > (INT_MAX - nb) / 10)
			return (0);
		acc = acc * 10 + nb;
		i++;
	}
	return (1);
}

int	check_overflow_long(char *str)
{
	int				i;
	unsigned long	acc;
	unsigned long	nb;

	i = 0;
	acc = 0;
	while (str[i])
	{
		nb = str[i] - 48;
		if (acc > (LONG_MAX - nb) / 10)
			return (0);
		acc = acc * 10 + nb;
		i++;
	}
	return (1);
}
