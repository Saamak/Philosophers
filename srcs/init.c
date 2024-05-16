/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:42:04 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:56:11 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	init_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		philo[i].l_fork = &forks[i];
		if (i == philo->nb_philo - 1)
			philo[i].r_fork = &forks[0];
		else
			philo[i].r_fork = &forks[i + 1];
		i++;
	}
}

t_philo	*init_struct(char **av, t_philo *philo,
		t_monitor *monitor, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].forks = nb_philo;
		philo[i].nb_philo = nb_philo;
		philo[i].dead = &monitor->dead;
		philo[i].time_to_die = atoi(av[2]);
		philo[i].time_to_eat = atoi(av[3]);
		philo[i].time_to_sleep = atoi(av[4]);
		philo[i].write_lock = &monitor->write_lock;
		philo[i].dead_lock = &monitor->dead_lock;
		philo[i].meal_lock = &monitor->meal_lock;
		if (av[5])
			philo[i].nb_eat = atoi(av[5]);
		else
			philo[i].nb_eat = -1;
		i++;
	}
	return (philo);
}

void	init_monitor(t_monitor *monitor)
{
	monitor->dead = 0;
	pthread_mutex_init(&monitor->write_lock, NULL);
	pthread_mutex_init(&monitor->dead_lock, NULL);
	pthread_mutex_init(&monitor->meal_lock, NULL);
}
