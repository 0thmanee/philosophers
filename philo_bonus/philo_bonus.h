/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:43:03 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/27 03:02:59 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_fork
{
	sem_t	sem_fork;
}	t_fork;

typedef struct s_program
{
	int				nbr_philos;
	int				t_t_die;
	int				t_t_eat;
	int				t_t_sleep;
	long long		start_date;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*data;
	sem_t			*eating;
	sem_t			*dead;
	pthread_t		eating_thread;
	int				eating_times;
	int				session;
	int				*childs_id;
}	t_program;

typedef struct s_philo
{
	int			philo_id;
	pthread_t	thread;
	long long	last_meal;
	t_program	*prog;
	int			*dead;
	int			eats;
}	t_philo;

long		ft_atoi(const char *str);
void		check_args(int ac, char *av[]);
t_program	init_data(int ac, char *av[]);
t_philo		*init_philos(t_program data);
void		display_helper(void);
int			ft_strcmp(const char *s1, const char *s2);
long long	curr_time(void);
long long	calc_time_diff(t_program *prog);
void		custom_usleep(unsigned int time);
void		custom_printf(t_philo *philo, char *str, long long date, int id);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		cleanup(t_program data);
void		*watcher_routine(void *philos);
int			start_routine(t_philo *philos, int id);
int			start_child_process(t_philo *philo, int index);
void		wait_processes(t_program prog);
void		start_sumulation(t_program	prog, t_philo *philos, int i);

#endif