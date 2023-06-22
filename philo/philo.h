/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:17:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/20 09:01:50 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdatomic.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define TAKE 5

typedef struct s_rules_datas
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_must_eat;
	int	t_sleep;
}	t_rules;

typedef struct s_table_events
{
	pthread_mutex_t		write_something;
	pthread_mutex_t		*fork_dispo;
	atomic_int			end;
	int					n_as_ated_enough;
	struct timeval		init_timestamp;
}	t_events;

typedef struct s_philo_datas
{
	t_rules					*rules;
	t_events				*events;
	char					*str_number;
	int						left_fork;
	int						right_fork;
	atomic_int				last_meal;
	int						number;
	int						as_eated;
}	t_philo;

/*INIT CONTROL STRUCTURES*/

t_events	*init_events(t_rules *rules);
t_philo		**init_philo_array(t_rules *rules, t_events *events);
t_rules		*init_rules(int argc, char **argv);

/*FREE MEMORY*/

void		free_all(t_rules *rul, t_events *ev, t_philo **ph, pthread_t *th);
void		free_philo_array(t_philo **philo_array, int n);
void		*handle_events_error(t_events *events, t_rules *rules);
void		*handle_rules_error(t_rules *rules);
void		destroy_mutex_array(pthread_mutex_t *t_array, int n);

/*ROUTINE*/

void		*start_routine(void *philo);
int			get_actual_timestamp(t_events *events);
int			write_something(t_philo *philo, int msg);

/*STRING MANAGEMENT UTILS*/

char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str, int *result);

#endif
