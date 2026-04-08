/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 20:45:02 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 12:18:58 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	populate_data(t_data *data, int ac, char **av)
{
	data->num_philos = (int)ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 5)
		data->meals_required = -1;
	else
		data->meals_required = (int)ft_atol(av[5]);
	data->stop = 0;
	data->start_time = 0;
	data->forks = NULL;
	data->philos = NULL;
	data->forks_init = 0;
	data->global_mutex = 0;
	data->threads_created = 0;
}

void	populate_philos(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = data->start_time;
	philo->data = data;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->num_philos];
	philo->forks_at_hand = 0;
}
