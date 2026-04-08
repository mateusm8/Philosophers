/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:22:55 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 12:29:06 by matmagal         ###   ########.fr       */
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

int	monitor_loop(t_data *data)
{
	int	i;
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
				return (set_stop(data, 1), print_death(&data->philos[i], now), 1);
			if (all_ate_enough(data))
				return (set_stop(data, 1), 1);
			usleep(500);
			i++;
		}
	}
	return (1);
}
