/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:22:55 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:10:04 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitor_loop(t_data *data)
{
	int		i;
	long	now;

	while (get_stop(data) == 0)
	{
		i = 0;
		while (i < data->num_philos)
		{
			now = get_time_ms();
			if (now == -1)
				return (0);
			if (philo_is_dead(&data->philos[i], now))
				return (set_stop(data, 1),
					print_death(&data->philos[i], now), 1);
			if (all_ate_enough(data))
				return (set_stop(data, 1), 1);
			usleep(500);
			i++;
		}
	}
	return (1);
}
