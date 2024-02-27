/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:41:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/27 02:53:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	custom_printf(t_philo *philo, char *str, long long date, int id)
{
	if (!(*philo->dead) || !ft_strcmp(str, "died"))
	{
		sem_wait(philo->prog->message);
		printf("%lld %d %s\n", date, id, str);
		if (ft_strcmp(str, "died"))
			sem_post(philo->prog->message);
	}
}

void	eating(t_philo *philo)
{
	sem_wait(philo->prog->forks);
	custom_printf(philo, "has taken a fork",
		calc_time_diff(philo->prog), philo->philo_id);
	sem_wait(philo->prog->forks);
	custom_printf(philo, "has taken a fork",
		calc_time_diff(philo->prog), philo->philo_id);
	sem_wait(philo->prog->data);
	philo->last_meal = curr_time();
	philo->eats++;
	sem_post(philo->prog->data);
	custom_printf(philo, "is eating",
		calc_time_diff(philo->prog), philo->philo_id);
	custom_usleep(philo->prog->t_t_eat);
	sem_post(philo->prog->forks);
	sem_post(philo->prog->forks);
}

void	sleeping(t_philo *philo)
{
	custom_printf(philo, "is sleeping",
		calc_time_diff(philo->prog), philo->philo_id);
	custom_usleep(philo->prog->t_t_sleep);
	if (philo->prog->eating_times != -1
		&& philo->eats >= philo->prog->eating_times)
		exit(EXIT_SUCCESS);
}

void	thinking(t_philo *philo)
{
	custom_printf(philo, "is thinking",
		calc_time_diff(philo->prog), philo->philo_id);
}

void	cleanup(t_program data)
{
	sem_close(data.forks);
	sem_close(data.message);
	sem_close(data.data);
	sem_close(data.eating);
	sem_close(data.dead);
	unlink("forks");
	unlink("message");
	unlink("data");
	unlink("eating");
	unlink("dead");
}
