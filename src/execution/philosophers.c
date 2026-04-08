/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:13:40 by matmagal          #+#    #+#             */
/*   Updated: 2026/04/08 15:10:30 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		monitor_status;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	parse(data, ac, av);
	if (!init_global_mutexes(data) || !init_forks(data)
		|| !init_philos(data) || !create_thread(data))
		return (cleanup(data), 1);
	monitor_status = monitor_loop(data);
	(join_threads(data), cleanup(data));
	if (!monitor_status)
		return (1);
	return (0);
}
