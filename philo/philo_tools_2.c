/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 04:50:44 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/19 04:53:22 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		;
}

long long	curr_time_2(void)
{
	struct timeval	te;
	long long		microseconds;

	gettimeofday(&te, NULL);
	microseconds = te.tv_sec * 1000000 + te.tv_usec;
	return (microseconds);
}

void	custom_usleep_2(unsigned int time)
{
	long long	micro;

	micro = curr_time();
	while (curr_time_2() - micro < time)
		;
}
