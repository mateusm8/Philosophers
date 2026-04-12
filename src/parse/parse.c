/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:32:08 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/12 18:01:01 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_positive_number(char	*number, int nb)
{
	long	value;

	if (!is_number(number))
		return (0);
	if (nb == 1 || nb == 5)
	{
		if (!check_overflow_int(number))
			return (0);
	}
	else
	{
		if (!check_overflow_long(number))
			return (0);
	}
	value = ft_atol(number);
	return (value);
}

static int	parse_args(int ac)
{
	if (ac < 5 || ac > 6)
		return (0);
	return (1);
}

void	parse(t_data *data, int ac, char **av)
{
	int	i;
	int	value;

	i = 1;
	value = 0;
	if (!parse_args(ac))
	{
		write(2, "Number of inputs are invalid.\n", 30);
		free(data);
		exit (1);
	}
	while (i < ac)
	{
		value = is_positive_number(av[i], i);
		if (value < 0 || (value == 0 && i != 5))
		{
			write(2, "One or more params are invalid.\n", 35);
			free(data);
			exit(1);
		}
		i++;
	}
	populate_data(data, av);
}
