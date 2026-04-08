/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:16:54 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:29:58 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		data->forks_init += 1;
		i++;
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		populate_philos(&data->philos[i], data, i);
		i++;
	}
	return (1);
}

int	init_global_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0)
		return (data->global_mutex = 1, 0);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (data->global_mutex = 2, 0);
	return (data->global_mutex = 3, 1);
}
