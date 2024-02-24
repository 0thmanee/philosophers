/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:45:49 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/23 22:24:24 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;
	long	tmp;

	i = 0;
	sign = 1;
	res = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9' && res < (long)INT_MAX + 1)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (sign * res);
}

int	not_int(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (1);
		i++;
	}
	if (ft_atoi(nbr) < -2147483648 || ft_atoi(nbr) > 2147483647)
		return (1);
	return (0);
}

void	check_args(int ac, char *av[])
{
	int		i;

	i = 0;
	if (ac != 5)
	{
		display_helper();
		exit(EXIT_FAILURE);
	}
	while (++i < ac)
	{
		if (not_int(av[i]) || ft_atoi(av[i]) < 0
			|| (i == 1 && ft_atoi(av[i]) > 200))
		{
			display_helper();
			exit(EXIT_FAILURE);
		}
	}
	while (++i < ac)
	{
		if ((i == 1 || i == 3) && ft_atoi(av[i]) == 0)
			exit(EXIT_FAILURE);
	}
}
