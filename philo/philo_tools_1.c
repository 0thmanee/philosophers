/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:51:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/19 04:52:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_helper(void)
{
	printf("\n\tInvalid Args :/\n\n\n");
	printf("\tFollow the structure: \n\n");
	printf("\t<< arg1: number_of_philosophers >>\n\n");
	printf("\t<< arg2: time_to_die >>\n\n");
	printf("\t<< arg3: time_to_eat >>\n\n");
	printf("\t<< arg4: time_to_sleep >>\n\n");
	printf("\t<< arg5 (Optional): ");
	printf("\t[number_of_times_each_philosopher_must_eat] >>\n\n");
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
