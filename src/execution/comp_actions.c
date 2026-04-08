/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:06:39 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 17:08:40 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_fork(t_philo *philo)
{
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;

	philo->forks_at_hand = 0;
	if (philo->left_fork == philo->right_fork)
	{
		if (pthread_mutex_lock(philo->left_fork) == 0)
			philo->forks_at_hand = 1;
		return ;
	}
	if (philo->left_fork < philo->right_fork)
		(f1 = philo->left_fork, f2 = philo->right_fork);
	else
		(f1 = philo->right_fork, f2 = philo->left_fork);
	if (pthread_mutex_lock(f1) != 0)
		return ;
	if (pthread_mutex_lock(f2) != 0)
	{
		pthread_mutex_unlock(f1);
		return ;
	}
	philo->forks_at_hand = 2;
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
