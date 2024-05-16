/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:38 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:54:28 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_death(t_philo *philo, int elapsed_time, int i)
{
	pthread_mutex_lock(philo[i].write_lock);
	printf(BOLD"%d %d %s\n", elapsed_time, philo[i].id, R"died"RESET);
	pthread_mutex_unlock(philo[i].write_lock);
}

void	print_action(t_philo *philo, char *action)
{
	int	elapsed_time;

	if (!(check_value_death(philo)))
	{
		pthread_mutex_lock(philo->write_lock);
		elapsed_time = get_current_time() - philo->start_time;
		printf(BOLD"%d %d is %s\n", elapsed_time, philo->id, action);
		pthread_mutex_unlock(philo->write_lock);
	}
}
