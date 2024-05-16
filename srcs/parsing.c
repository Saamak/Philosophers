/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:58:39 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/16 15:58:41 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	is_not_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (atoi(av[i]) <= 0)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (!(ac >= 4 && ac <= 6))
	{
		printf(BOLD"%sError %s: this program needs 4 or 5 arguments\n",
			R, RESET);
		return (1);
	}
	if (is_not_digit(av))
	{
		printf(BOLD"%sError %s: please enter positives digits\n", R, RESET);
		return (1);
	}
	return (0);
}
