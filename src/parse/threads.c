/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:08:47 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 16:49:51 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	else
		usleep((philo->data->time_to_eat / 2) * 1000);
	while (get_stop(philo->data) == 0)
	{
		if (get_stop(philo->data) == 0)
			philo_eat(philo);
		if (get_stop(philo->data) == 0)
			philo_sleep(philo);
		if (get_stop(philo->data) == 0)
			philo_think(philo);
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	if (data->start_time == -1)
		return (0);
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (join_threads(data), 0);
		data->threads_created++;
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->threads_created)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
