/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:24:49 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/22 12:43:13 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define END_OF_SIMULATION 2

# define R   "\x1B[31m"
# define G   "\x1B[32m"
# define Y   "\x1B[33m"
# define BOLD "\x1B[1m"
# define RESET "\x1B[0m"

typedef struct s_monitoring
{
	pthread_t		thread;
	int				dead;
	int				meal;
	int				nbr_eat;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_monitor;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				*dead;
	int				*meal;
	int				forks;
	int				start_time;
	int				last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

// Init
void	init_forks(t_philo *philo, pthread_mutex_t *forks);
t_philo	*init_struct(char **av, t_philo *philo,
			t_monitor *monitor, int nb_philo);
void	init_monitor(t_monitor *monitor);

// Utils
int		check_args(int ac, char **av);
int		ft_usleep(size_t milliseconds);
int		check_all_death(t_philo *philo, t_monitor *monitor);
int		check_value_death(t_philo *philo);
void	choose_fork(t_philo *philo, pthread_mutex_t **first_fork,
			pthread_mutex_t **second_fork);
void	thread_join(t_philo *philo);
int		all_eat(t_philo *philo);
int		check_value_meal(t_philo *philo);
int		ft_atoi(const char *str);

// Print
void	print_infos(t_philo *philo);
void	print_fork_add(t_philo *philo);
void	print_action(t_philo *philo, char *action);
void	print_take_fork(t_philo *philo, char *fork);
void	print_death(t_philo *philo, int elapsed_time, int i);

// Time
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

//Actions
int		is_eating(t_philo *philo);
void	eating(t_philo *philo, pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork);
int		is_sleeping(t_philo *philo);
int		is_thinking(t_philo *philo);

#endif
