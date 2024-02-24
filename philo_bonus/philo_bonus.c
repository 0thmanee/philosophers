/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:42:06 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/24 21:22:25 by obouchta         ###   ########.fr       */
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
		if (philo->eats >= philo->prog->eating_times)
			sem_post(philo->prog->eating);
		if (curr_time() - philo->last_meal >= philo->prog->t_t_die)
		{
			*(philo->dead) = 1;
			custom_printf(philo, "died",
				calc_time_diff(philo->prog), philo->philo_id);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->prog->data);
	}
	return (NULL);
}

int	start_simulation(t_philo *philos, int id)
{
	if (pthread_create(&(philos[id].thread), NULL,
		watcher_routine, (void *)philos))
		return (0);
	pthread_detach(philos[id].thread);
	while (1)
	{
		thinking(philos);
		eating(philos);
		sleeping(philos);
	}
	return (1);
}

int	start_child_process(t_philo *philo, int index)
{
	if (!start_simulation(philo, index))
		return 0;
	if (index % 2)
		custom_usleep(1);
	return 1;
}

void	cleanup(t_program data, int *childs_id)
{
	if (wait(NULL) != -1)
	{
		int i = -1;
		while (++i < data.nbr_philos)
			kill(childs_id[i], SIGKILL);
	}
}

void *eating_times_routine(void *data)
{
	t_program	*prog;
	int			i;

	prog = (t_program *)data;
	i = -1;
	while (++i < prog->nbr_philos)
		sem_wait(prog->eating);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_program	data;
	t_philo		*philos;
	int			*childs_id;
	int			i;
	int			id;
	
	(1 == 1) && (check_args(ac, av), data = init_data(ac, av),
		philos = init_philos(data), childs_id = NULL);
	if (!philos)
		exit(EXIT_FAILURE);
	childs_id = malloc(data.nbr_philos * sizeof(int));
	if (!childs_id)
		exit(EXIT_FAILURE);
	i = -1;
	// if (pthread_create(&data.eating_thread, NULL, eating_times_routine, (void *)&data))
	// 	exit(EXIT_FAILURE);
	// pthread_detach(data.eating_thread);
	while (++i < data.nbr_philos)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (id == 0 && !start_child_process(&philos[i], i))
			exit(EXIT_FAILURE);
		else if (id != 0)
			childs_id[i] = id;
	}
	(cleanup(data, childs_id), exit(EXIT_SUCCESS));
}
