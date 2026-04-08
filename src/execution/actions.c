/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:56 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 13:05:02 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_philo *philo)
{
	long	now;
	
	if (get_stop(philo->data))
		return ;
	now = get_time_ms();
	if (now == -1)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d is thinking\n", now - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	philo_eat(t_philo *philo)
{
	long	now;

	if (get_stop(philo->data))
		return ;
	lock_fork(philo);
	now = get_time_ms();
	if (now == -1)
	{
		unlock_fork(philo);
		return ;
	}
	if (philo->forks_at_hand == 2)
		eat_action(philo, now);
	else if (philo->forks_at_hand == 1)
	{
		wait_for_stop(philo);
		return ;
	}
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (get_stop(philo->data))
		return ;
	now = get_time_ms();
	if (now == -1)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d is sleeping\n", now - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	usleep(philo->data->time_to_sleep * 1000);
}

void	lock_fork(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo->forks_at_hand = 2;
	}
	else if (philo->right_fork < philo->left_fork)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		philo->forks_at_hand = 2;
	}
	else if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->forks_at_hand = 1;
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->forks_at_hand = 0;
	}
	else if (philo->right_fork < philo->left_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->forks_at_hand = 0;
	}
	else if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->forks_at_hand = 0;
	}
}

void	wait_for_stop(t_philo *philo)
{
	while (get_stop(philo->data) == 0)
		usleep(500);
	unlock_fork(philo);
}

void	eat_action(t_philo *philo, long now)
{
		if (get_stop(philo->data) == 1)
		{
			unlock_fork(philo);
			return ;
		}
		pthread_mutex_lock(&philo->data->meal_lock);
		philo->last_meal = now;
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->data->meal_lock);
		pthread_mutex_lock(&philo->data->write_lock);
		if (get_stop(philo->data) == 1)
		{
			pthread_mutex_unlock(&philo->data->write_lock);
			unlock_fork(philo);
			return ;
		}
		printf("%ld %d is eating\n", now - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write_lock);
		usleep(philo->data->time_to_eat * 1000);
		unlock_fork(philo);
}
