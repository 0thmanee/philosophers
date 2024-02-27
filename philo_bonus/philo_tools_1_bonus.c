/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:52:27 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/26 20:48:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long long	curr_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

long long	calc_time_diff(t_program *prog)
{
	long long	curr;

	curr = curr_time();
	return (curr - prog->start_date);
}

void	custom_usleep(unsigned int time)
{
	long long	milli;

	milli = curr_time();
	while (curr_time() - milli < time)
		usleep(500);
}
