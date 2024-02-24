/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:41:33 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/19 04:49:39 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mut_fork;
}	t_fork;

typedef struct s_philo
{
	int			philo_id;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread;
	int			eats;
	long long	last_meal;
}	t_philo;

typedef struct s_program
{
	int				nbr_philos;
	int				t_t_die;
	int				t_t_eat;
	int				t_t_sleep;
	int				eating_times;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_lead;
	pthread_mutex_t	mut_session;
	long long		start_date;
	int				session;
	t_philo			*philos;
	t_fork			*forks;
}	t_program;

typedef struct s_waiter
{
	pthread_t	thread;
	t_program	*prog;
}	t_waiter;

typedef struct s_all
{
	t_program	*prog;
	int			philo_id;
}	t_all;

long		ft_atoi(const char *str);
int			valid_args(int ac, char *av[]);
long long	calc_time_diff(t_program *prog);
void		custom_usleep(unsigned int time);
void		custom_usleep_2(unsigned int time);
void		display_helper(void);
long long	curr_time(void);
t_program	init_data(int ac, char *av[]);
t_fork		*init_forks(t_program *data);
t_philo		*init_philos(t_program data);
void		custom_printf(t_program *prog, char *str, long long date, int id);
void		*routine_waiter(void *data);
void		*routine(void *data);
int			create_threads(t_all **g, t_program data, t_waiter *waiter, int i);
int			ft_strcmp(const char *s1, const char *s2);

#endif