/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:07:56 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:37:19 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	get_stop(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->stop_lock);
	value = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (value);
}

void	set_stop(t_data *data, int value)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop = value;
	pthread_mutex_unlock(&data->stop_lock);
}
