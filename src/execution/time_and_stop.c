/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:07:56 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/12 19:51:52 by matmagal         ###   ########.fr       */
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

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (get_stop(philo->data) == 0)
		printf("%ld %d has taken a fork\n",
			get_time_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	sleep_until(long time_to_awake, t_data *data)
{
	while (get_time_ms() < time_to_awake)
	{
		usleep(500);
		if (get_stop(data) != 0)
			break ;
	}
}
