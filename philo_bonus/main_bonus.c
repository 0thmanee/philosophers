/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:01:55 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/27 03:03:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (++i < data.nbr_philos)
		kill(data.childs_id[i], SIGINT);
	cleanup(data);
	exit(EXIT_SUCCESS);
}
