/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:41:25 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/25 19:14:24 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_enough(t_program *prog)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (prog->eating_times != -1)
	{
		while (i < prog->nbr_philos)
		{
			if (prog->philos[i].eats >= prog->eating_times)
				count++;
			i++;
		}
		if (count >= prog->nbr_philos)
			return (1);
	}
	return (0);
}

int	check_session(t_waiter *waiter, int i)
{
	pthread_mutex_lock(&waiter->prog->mut_lead);
	if (curr_time() - waiter->prog->philos[i].last_meal
		> waiter->prog->t_t_die)
	{
		pthread_mutex_lock(&waiter->prog->mut_session);
		waiter->prog->session = 0;
		pthread_mutex_unlock(&waiter->prog->mut_session);
		custom_printf(waiter->prog, "died",
			calc_time_diff(waiter->prog), i + 1);
		pthread_mutex_unlock(&waiter->prog->mut_lead);
		return (0);
	}
	pthread_mutex_unlock(&waiter->prog->mut_lead);
	if (eat_enough(waiter->prog))
	{
		pthread_mutex_lock(&waiter->prog->mut_session);
		waiter->prog->session = 0;
		pthread_mutex_unlock(&waiter->prog->mut_session);
		return (0);
	}
	return (1);
}

void	*routine_waiter(void *data)
{
	t_waiter	*waiter;
	int			i;

	waiter = (t_waiter *)data;
	while (1)
	{
		if (waiter->prog->nbr_philos == 1)
			return (NULL);
		i = -1;
		while (++i < waiter->prog->nbr_philos)
		{
			if (!check_session(waiter, i))
				return (NULL);
		}
	}
	return (NULL);
}

void	free_data(t_program *data, t_waiter *waiter, t_all **prog_phils)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_lead);
	pthread_mutex_destroy(&data->mut_session);
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philos[i].r_fork->mut_fork);
		free(prog_phils[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
	free(prog_phils);
	free(waiter);
}

int	main(int ac, char *av[])
{
	t_program	data;
	t_all		**prog_phils;
	t_waiter	*waiter;

	if (!valid_args(ac, av))
		return (1);
	(1 == 1) && (prog_phils = NULL, waiter = NULL, data = init_data(ac, av),
		data.forks = init_forks(&data));
	if (!data.forks)
		return (1);
	data.philos = init_philos(data);
	if (!data.philos)
		return (1);
	prog_phils = malloc(data.nbr_philos * sizeof(t_all *));
	if (!prog_phils)
		return (1);
	waiter = malloc(sizeof(t_waiter));
	if (!waiter)
		return (1);
	if (!create_threads(prog_phils, data, waiter, 0))
		return (1);
	free_data(&data, waiter, prog_phils);
	return (0);
}
