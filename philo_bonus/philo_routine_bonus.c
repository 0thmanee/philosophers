/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:41:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/24 20:45:08 by obouchta         ###   ########.fr       */
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
	sem_post(philo->prog->data);
	custom_printf(philo, "is eating",
		calc_time_diff(philo->prog), philo->philo_id);
	sem_wait(philo->prog->data);
	philo->eats++;
	sem_post(philo->prog->data);
	custom_usleep(philo->prog->t_t_eat);
	sem_post(philo->prog->forks);
	sem_post(philo->prog->forks);
}

void	sleeping(t_philo *philo)
{
	custom_printf(philo, "is sleeping",
		calc_time_diff(philo->prog), philo->philo_id);
	custom_usleep(philo->prog->t_t_sleep);
}

void	thinking(t_philo *philo)
{
	custom_printf(philo, "is thinking",
		calc_time_diff(philo->prog), philo->philo_id);
}