/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:31:24 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:55:10 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	is_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	choose_fork(philo, &first_fork, &second_fork);
	if (check_value_death(philo) == 1 || philo->nb_eat == 0)
		return (END_OF_SIMULATION);
	pthread_mutex_lock(first_fork);
	if (check_value_death(philo) == 1)
	{
		pthread_mutex_unlock(first_fork);
		return (END_OF_SIMULATION);
	}
	pthread_mutex_lock(second_fork);
	if (check_value_death(philo) == 1)
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (END_OF_SIMULATION);
	}
	print_action(philo, G"eating"RESET);
	eating(philo, first_fork, second_fork);
	return (SUCCESS);
}

int	is_sleeping(t_philo *philo)
{
	if (check_value_death(philo) == 0)
		print_action(philo, Y"sleeping"RESET);
	else
		return (END_OF_SIMULATION);
	ft_usleep(philo->time_to_sleep);
	return (SUCCESS);
}

int	is_thinking(t_philo *philo)
{
	if (check_value_death(philo) == 0)
		print_action(philo, "thinking");
	else
		return (END_OF_SIMULATION);
	return (SUCCESS);
}
