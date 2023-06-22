/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:35:07 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/10 15:56:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define TAKE 5
# define END 6

typedef struct s_rules_datas
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_must_eat;
	int				t_sleep;
}	t_rules;

typedef struct s_table_events
{
	sem_t			*write_something;
	sem_t			*fork_dispo;
	sem_t			*end_simu;
	sem_t			*eated_enough;
	int				n_as_ated_enough;
	struct timeval	init_timestamp;
}	t_events;

typedef struct s_philo_datas
{
	t_rules					*rules;
	t_events				*events;
	char					*str_number;
	int						str_number_len;
	atomic_int				last_meal;
	int						number;
	int						as_eated;
	pid_t					pid;
}	t_philo;

/*INIT CONTROL STRUCTURES*/

t_rules		*init_rules(int argc, char **argv);
t_events	*init_events(t_rules *rules);
t_philo		**init_philo_array(t_rules *rules, t_events *events);

/*FREE MEMORY*/

void		*handle_rules_error(t_rules *rules);
void		*handle_events_error(t_events *events, t_rules *rules);
void		free_philo_array(t_philo **philo_array, int n);
void		free_all(t_rules *rul, t_events *ev, t_philo **ph);
void		close_and_unlink_sem(t_events *events);

/*ROUTINE*/

void		*philo_routine(t_philo *philo);
int			write_something(t_philo *philo, int msg);
int			get_time(t_events *events);

/*STRING MANAGEMENT UTILS*/

char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str, int *result);

#endif
