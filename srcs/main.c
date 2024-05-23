/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:45:46 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/22 12:45:33 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	handle_death(t_philo *philo, int i)
{
	int	elapsed_time;

	elapsed_time = get_current_time() - philo->start_time;
	print_death(philo, elapsed_time, i);
	*philo[i].dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	check_all_death(t_philo *philo, t_monitor *monitor)
{
	int	i;
	int	time_since_last_meal;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (monitor->nbr_eat == 0 && all_eat(philo))
			return (1);
		pthread_mutex_lock(philo->meal_lock);
		time_since_last_meal = get_current_time() - philo[i].last_meal;
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->dead_lock);
		if (time_since_last_meal > philo[i].time_to_die)
			return (handle_death(philo, i));
		pthread_mutex_unlock(philo->dead_lock);
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
		if (check_value_death(philo) == 1 || check_value_meal(philo) == 1)
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

void	gen_threads(t_philo *philo, t_monitor *monitor)
{
	int	i;

	i = 0;
	if (philo->nb_eat == -1)
		monitor->nbr_eat = 1;
	while (i < philo->nb_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]);
		i++;
	}
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
	nb_philo = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * nb_philo);
	philo = init_struct(av, philo, &monitor, nb_philo);
	forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	init_forks(philo, forks);
	gen_threads(philo, &monitor);
	while (1)
	{
		if (check_all_death(philo, &monitor))
			break ;
	}
	thread_join(philo);
	free(forks);
	free(philo);
	return (0);
}
