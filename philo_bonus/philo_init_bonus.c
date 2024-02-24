/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:48:43 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/24 11:04:00 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_program	init_data(int ac, char *av[])
{
	t_program	data;

	(void)ac;
	data.nbr_philos = ft_atoi(av[1]);
	data.t_t_die = ft_atoi(av[2]);
	data.t_t_eat = ft_atoi(av[3]);
	data.t_t_sleep = ft_atoi(av[4]);
	data.start_date = curr_time();
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("data");
	data.forks = sem_open("forks", O_CREAT, 0600, data.nbr_philos);
	data.message = sem_open("message", O_CREAT, 0600, 1);
	data.data = sem_open("data", O_CREAT, 0600, 1);
	return (data);
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
		philos[i].prog = &data;
		philos[i].dead = malloc(sizeof(int));
		*(philos[i].dead) = 0;
		philos[i].last_meal = curr_time();
		philos[i].eats = 0;
		i++;
	}
	return (philos);
}
