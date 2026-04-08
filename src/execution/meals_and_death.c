/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_and_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:08:55 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:13:28 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (last_meal);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(&philo->data->meal_lock);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (meals_eaten);
}

int	philo_is_dead(t_philo *philo, long now)
{
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_lock);
	if ((now - last_meal) > philo->data->time_to_die)
		return (1);
	else
		return (0);
}

int	all_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_required == -1)
		return (0);
	while (i < data->num_philos)
	{
		if (get_meals_eaten(&data->philos[i]) < data->meals_required)
			return (0);
		i++;
	}
	return (1);
}

void	print_death(t_philo *philo, long now)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %i died\n", (now - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}
