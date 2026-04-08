/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:40:39 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:13:54 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->forks_init)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->global_mutex == 1)
		pthread_mutex_destroy(&data->write_lock);
	else if (data->global_mutex == 2)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->stop_lock);
	}
	else if (data->global_mutex == 3)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->stop_lock);
		pthread_mutex_destroy(&data->meal_lock);
	}
	free(data->forks);
	free(data->philos);
	free(data);
}

void	cleanup(t_data *data)
{
	if (data)
		clean_data(data);
}
