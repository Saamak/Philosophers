/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:45:46 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:59:18 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_all_death(t_philo *philo)
{
	int	i;
	int	time_since_last_meal;
	int	elapsed_time;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (get_time_since_last_meal(philo, i, &time_since_last_meal))
			return (1);
		if (*philo[i].dead == 0 && time_since_last_meal > philo[i].time_to_die)
		{
			elapsed_time = get_current_time() - philo->start_time;
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			print_death(philo, elapsed_time, i);
			return (1);
		}
		if (i == philo->nb_philo)
			i = 0;
		else
			i++;
	}
	return (0);
}

static void	*routine(void *params)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = params;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (check_value_death(philo))
			break ;
		if (is_eating(philo) == END_OF_SIMULATION)
			break ;
		if (check_value_death(philo))
			break ;
		if (is_sleeping(philo) == END_OF_SIMULATION)
			break ;
		if (check_value_death(philo))
			break ;
		else if (is_thinking(philo) == END_OF_SIMULATION)
			break ;
	}
	return (SUCCESS);
}

void	*monitoring(void *params)
{
	t_philo	*philo;

	philo = params;
	while (1)
	{
		if (check_all_death(philo))
			break ;
	}
	return (SUCCESS);
}

void	gen_threads(t_philo *philo, t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor->thread, NULL, monitoring, philo);
}

int	main(int ac, char **av)
{
	int				nb_philo;
	t_philo			*philo;
	t_monitor		monitor;
	pthread_mutex_t	*forks;

	philo = NULL;
	if (check_args(ac, av))
		return (1);
	init_monitor(&monitor);
	nb_philo = atoi(av[1]);
	philo = malloc(sizeof(t_philo) * nb_philo);
	philo = init_struct(av, philo, &monitor, nb_philo);
	forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	init_forks(philo, forks);
	gen_threads(philo, &monitor);
	thread_join(philo, monitor);
	free(forks);
	free(philo);
	return (0);
}
