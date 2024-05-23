/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:28 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/18 18:40:32 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			printf("Error joining thread\n");
			return ;
		}
		i++;
	}
}

int	check_value_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (*philo->meal == 1)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	all_eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->meal_lock);
	while (i < philo->nb_philo)
	{
		if (philo[i].nb_eat > 0)
		{
			pthread_mutex_unlock(philo->meal_lock);
			return (0);
		}
		i++;
	}
	*philo->meal = 1;
	pthread_mutex_unlock(philo->meal_lock);
	return (1);
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
