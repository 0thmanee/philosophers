/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:42:06 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/27 03:02:15 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*watcher_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		sem_wait(philo->prog->data);
		if (curr_time() - philo->last_meal >= philo->prog->t_t_die)
		{
			sem_wait(philo->prog->dead);
			*(philo->dead) = 1;
			sem_post(philo->prog->dead);
			custom_printf(philo, "died",
				calc_time_diff(philo->prog), philo->philo_id);
			sem_post(philo->prog->data);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->prog->data);
	}
	return (NULL);
}

int	start_routine(t_philo *philos, int id)
{
	if (pthread_create(&(philos[id].thread), NULL,
			watcher_routine, (void *)philos))
		return (0);
	pthread_detach(philos[id].thread);
	while (1)
	{
		if (philos->prog->nbr_philos == 1)
		{
			custom_usleep(philos->prog->t_t_die);
			custom_printf(philos, "died",
				calc_time_diff(philos->prog), philos->philo_id);
			exit(EXIT_SUCCESS);
		}
		thinking(philos);
		eating(philos);
		sleeping(philos);
	}
	return (1);
}

int	start_child_process(t_philo *philo, int index)
{
	if (index % 2)
		custom_usleep(philo->prog->t_t_eat);
	if (!start_routine(philo, index))
		return (0);
	return (1);
}

void	wait_processes(t_program prog)
{
	int	i;
	int	status;

	i = 0;
	while (i < prog.nbr_philos)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == 0)
			i++;
		else if (status >> 8 == 1)
		{
			i = -1;
			while (++i < prog.nbr_philos)
				kill(prog.childs_id[i], SIGINT);
			break ;
		}
	}
}

void	start_sumulation(t_program	prog, t_philo *philos, int i)
{
	int			id;

	while (++i < prog.nbr_philos)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (id == 0 && !start_child_process(&philos[i], i))
			exit(EXIT_FAILURE);
		else if (id != 0)
			prog.childs_id[i] = id;
	}
	i = 0;
	wait_processes(prog);
}
