/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:42:06 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/27 01:15:08 by obouchta         ###   ########.fr       */
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
		if (philo->prog->eating_times != -1
			&& philo->eats >= philo->prog->eating_times)
		{
			sem_post(philo->prog->data);
			exit(EXIT_SUCCESS);
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
	if (!start_routine(philo, index))
		return (0);
	if (index % 2)
		custom_usleep(2);
	return (1);
}

void	start_sumulation(t_program	prog, t_philo *philos, int i)
{
	int			status;
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
	i = -1;
	while (++i < prog.nbr_philos)
	{
		waitpid(prog.childs_id[i], &status, 0);
		if (status)
		{
			i = -1;
			while (i++ < prog.nbr_philos)
				kill(prog.childs_id[i], SIGINT);
		}
	}
	exit(EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_program	data;
	t_philo		*philos;
	int			i;

	(1 == 1) && (check_args(ac, av), data = init_data(ac, av),
		philos = init_philos(data), data.childs_id = NULL);
	if (!philos)
		exit(EXIT_FAILURE);
	data.childs_id = malloc(data.nbr_philos * sizeof(int));
	if (!data.childs_id)
		exit(EXIT_FAILURE);
	start_sumulation(data, philos, -1);
	i = -1;
	while (i++ < data.nbr_philos)
		kill(data.childs_id[i], SIGINT);
	cleanup(data);
	exit(EXIT_SUCCESS);
}
