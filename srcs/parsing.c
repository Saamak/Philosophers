/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:58:39 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/22 12:45:09 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = sign * -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + str[i] - 48;
			i++;
		}
		return (result * sign);
	}
	return (0);
}

int	is_not_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
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
	if (!(ac >= 5 && ac <= 6))
	{
		printf(BOLD"%sError %s: this program needs 4 or 5 arguments\n",
			R, RESET);
		return (1);
	}
	if (ft_atoi(av[1]) == 1)
	{
		printf(BOLD"%d 1 died \n", ft_atoi(av[2]));
		return (1);
	}
	if (is_not_digit(av))
	{
		printf(BOLD"%sError %s: please enter positives digits\n", R, RESET);
		return (1);
	}
	return (0);
}
