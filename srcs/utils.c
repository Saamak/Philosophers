/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:28 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:59:24 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	thread_join(t_philo *philo, t_monitor monitor)
{
	int	i;

	i = 1;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			printf("Error joining thread\n");
			return ;
		}
		i++;
	}
	if (pthread_join(monitor.thread, NULL) != 0)
	{
		printf("Error joining thread\n");
		return ;
	}
}

int	get_time_since_last_meal(t_philo *philo,
	int i, int *time_since_last_meal)
{
	pthread_mutex_lock(philo->meal_lock);
	*time_since_last_meal = get_current_time() - philo[i].last_meal;
	if (philo[i].nb_eat == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

void	choose_fork(t_philo *philo,
		pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->l_fork < philo->r_fork)
	{
		*first_fork = philo->l_fork;
		*second_fork = philo->r_fork;
	}
	else
	{
		*first_fork = philo->r_fork;
		*second_fork = philo->l_fork;
	}
}

int	check_value_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	eating(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->nb_eat--;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
