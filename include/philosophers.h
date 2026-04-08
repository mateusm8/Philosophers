
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct	s_philo
{
	int	id;
	int	meals_eaten;
	int	forks_at_hand;
	long	last_meal;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int		num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		meals_required;
	long	start_time;
	int		stop;
	int		forks_init;
	int		threads_created;
	int		global_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_data;


long	ft_atol(const char *str);
void	parse(t_data *data, int ac, char **av);
void	populate_data(t_data *data, int ac, char **av);
void	populate_philos(t_philo *philo, t_data *data, int i);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
int		init_global_mutexes(t_data *data);
void	cleanup(t_data *data);
int		join_threads(t_data *data);
int		create_thread(t_data *data);
long	get_time_ms(void);
int		monitor_loop(t_data *data);
void	print_death(t_philo *philo, long now);
int		all_ate_enough(t_data *data);
int		philo_is_dead(t_philo *philo, long now);
int		get_meals_eaten(t_philo *philo);
long	get_last_meal(t_philo *philo);
void	set_stop(t_data *data, int value);
int		get_stop(t_data *data);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	lock_fork(t_philo *philo);
void	unlock_fork(t_philo *philo);
void	wait_for_stop(t_philo *philo);
void	eat_action(t_philo *philo, long now);

#endif
