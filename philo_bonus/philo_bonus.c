/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:42:06 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/25 15:41:10 by obouchta         ###   ########.fr       */
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
		if (philo->prog->eating_times != -1 &&
			philo->eats > philo->prog->eating_times)
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

void	cleanup(t_program data, int mode)
{
	int i;

	i = -1;
	if (mode == 1 || wait(NULL) != -1)
	{
		while (++i < data.nbr_philos)
			kill(data.childs_id[i], SIGKILL);
	}
	sem_close(data.forks);
	sem_close(data.message);
	sem_close(data.data);
	sem_close(data.eating);
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("data");
	sem_unlink("eating_times");
	free(data.childs_id);
}

void *eating_times_routine(void *data)
{
	t_program	*prog;
	int			i;

	prog = (t_program *)data;
	i = -1;
	while (++i < prog->nbr_philos)
		sem_wait(prog->eating);
	cleanup(*prog, 1);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_program	data;
	t_philo		*philos;
	int			i;
	int			id;
	
	(1 == 1) && (check_args(ac, av), data = init_data(ac, av),
		philos = init_philos(data), data.childs_id = NULL);
	if (!philos)
		exit(EXIT_FAILURE);
	data.childs_id = malloc(data.nbr_philos * sizeof(int));
	if (!data.childs_id)
		exit(EXIT_FAILURE);
	i = -1;
	if (pthread_create(&data.eating_thread, NULL, eating_times_routine, (void *)&data))
		exit(EXIT_FAILURE);
	pthread_detach(data.eating_thread);
	while (++i < data.nbr_philos)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (id == 0 && !start_child_process(&philos[i], i))
			exit(EXIT_FAILURE);
		else if (id != 0)
			data.childs_id[i] = id;
	}
	(cleanup(data, 0), exit(EXIT_SUCCESS));
}
