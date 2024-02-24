/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:36:18 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/19 02:17:26 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_program	init_data(int ac, char *av[])
{
	t_program	data;

	data.nbr_philos = ft_atoi(av[1]);
	data.t_t_die = ft_atoi(av[2]);
	data.t_t_eat = ft_atoi(av[3]);
	data.t_t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.eating_times = ft_atoi(av[5]);
	else
		data.eating_times = -1;
	data.start_date = curr_time();
	data.session = 1;
	return (data);
}

t_fork	*init_forks(t_program *data)
{
	t_fork	*forks;
	int		i;

	if (pthread_mutex_init(&data->mut_print, NULL))
		return (NULL);
	if (pthread_mutex_init(&data->mut_lead, NULL))
		return (NULL);
	if (pthread_mutex_init(&data->mut_session, NULL))
		return (NULL);
	forks = malloc(data->nbr_philos * sizeof(t_fork));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&forks[i].mut_fork, NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_program data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(data.nbr_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data.nbr_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].eats = 0;
		philos[i].r_fork = &data.forks[i];
		philos[i].last_meal = curr_time();
		if (i == data.nbr_philos - 1)
			philos[i].l_fork = data.forks;
		else
			philos[i].l_fork = &data.forks[i + 1];
		i++;
	}
	return (philos);
}

// g is prog_phils in create_threads function

int	create_threads(t_all **g, t_program data, t_waiter *waiter, int i)
{
	waiter->prog = &data;
	if (pthread_create(&waiter->thread, NULL, routine_waiter, (void *)waiter))
		return (0);
	pthread_detach(waiter->thread);
	i = -1;
	while (++i < data.nbr_philos)
	{
		g[i] = malloc(sizeof(t_all));
		if (!g)
			return (0);
		g[i]->prog = &data;
		g[i]->philo_id = i + 1;
		if (pthread_create(&data.philos[i].thread, NULL, routine, (void *)g[i]))
			return (0);
		if (!(i % 2))
			custom_usleep(1);
	}
	i = -1;
	while (++i < data.nbr_philos)
	{
		if (pthread_join(data.philos[i].thread, NULL))
			return (1);
	}
	return (1);
}
