/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:56 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:07:21 by matmagal         ###   ########.fr       */
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
