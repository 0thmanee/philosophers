/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:15:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/22 12:43:55 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	custom_printf(t_program *prog, char *str, long long date, int id)
{
	pthread_mutex_lock(&prog->mut_session);
	if (prog->session || !ft_strcmp(str, "died"))
	{
		pthread_mutex_lock(&prog->mut_print);
		printf("%lld %d %s\n", date, id, str);
		pthread_mutex_unlock(&prog->mut_print);
	}
	pthread_mutex_unlock(&prog->mut_session);
}

void	eating(t_all *prog_phils)
{
	pthread_mutex_lock(&prog_phils->prog->philos[prog_phils->philo_id
		- 1].r_fork->mut_fork);
	custom_printf(prog_phils->prog, "has taken a fork",
		calc_time_diff(prog_phils->prog), prog_phils->philo_id);
	pthread_mutex_lock(&prog_phils->prog->philos[prog_phils->philo_id
		- 1].l_fork->mut_fork);
	custom_printf(prog_phils->prog, "has taken a fork",
		calc_time_diff(prog_phils->prog), prog_phils->philo_id);
	pthread_mutex_lock(&prog_phils->prog->mut_lead);
	prog_phils->prog->philos[prog_phils->philo_id - 1].last_meal = curr_time();
	pthread_mutex_unlock(&prog_phils->prog->mut_lead);
	custom_printf(prog_phils->prog, "is eating",
		calc_time_diff(prog_phils->prog), prog_phils->philo_id);
	pthread_mutex_lock(&prog_phils->prog->mut_lead);
	prog_phils->prog->philos[prog_phils->philo_id - 1].eats++;
	pthread_mutex_unlock(&prog_phils->prog->mut_lead);
	custom_usleep(prog_phils->prog->t_t_eat);
	pthread_mutex_unlock(&prog_phils->prog->philos[prog_phils->philo_id
		- 1].l_fork->mut_fork);
	pthread_mutex_unlock(&prog_phils->prog->philos[prog_phils->philo_id
		- 1].r_fork->mut_fork);
}

void	sleeping(t_all *prog_phils)
{
	pthread_mutex_lock(&prog_phils->prog->mut_session);
	if (!prog_phils->prog->session)
	{
		pthread_mutex_unlock(&prog_phils->prog->mut_session);
		return ;
	}
	pthread_mutex_unlock(&prog_phils->prog->mut_session);
	custom_printf(prog_phils->prog, "is sleeping",
		calc_time_diff(prog_phils->prog), prog_phils->philo_id);
	custom_usleep(prog_phils->prog->t_t_sleep);
}

void	thinking(t_all *prog_phils)
{
	pthread_mutex_lock(&prog_phils->prog->mut_session);
	if (!prog_phils->prog->session)
	{
		pthread_mutex_unlock(&prog_phils->prog->mut_session);
		return ;
	}
	pthread_mutex_unlock(&prog_phils->prog->mut_session);
	custom_printf(prog_phils->prog, "is thinking",
		calc_time_diff(prog_phils->prog),
		prog_phils->philo_id);
}

void	*routine(void *data)
{
	t_all	*prog_phils;
	int		end;

	end = 0;
	prog_phils = (t_all *)data;
	while (1)
	{
		if (prog_phils->prog->nbr_philos == 1)
		{
			return (custom_usleep(prog_phils->prog->t_t_die),
				custom_printf(prog_phils->prog, "died",
					calc_time_diff(prog_phils->prog), 1), NULL);
		}
		pthread_mutex_lock(&prog_phils->prog->mut_session);
		if (!prog_phils->prog->session)
		{
			pthread_mutex_unlock(&prog_phils->prog->mut_session);
			return (NULL);
		}
		pthread_mutex_unlock(&prog_phils->prog->mut_session);
		thinking(prog_phils);
		eating(prog_phils);
		sleeping(prog_phils);
	}
	return (NULL);
}
