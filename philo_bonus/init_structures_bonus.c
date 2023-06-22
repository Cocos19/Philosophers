/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:31:10 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/09 20:49:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philo(t_rules *rules, t_events *events, int n)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->str_number = ft_itoa(n);
	if (!philo->str_number)
	{
		free(philo);
		return (NULL);
	}
	philo->str_number_len = ft_strlen(philo->str_number);
	philo->last_meal = get_time(events);
	philo->pid = -1;
	philo->rules = rules;
	philo->events = events;
	philo->number = n;
	philo->as_eated = 0;
	return (philo);
}

t_philo	**init_philo_array(t_rules *rules, t_events *events)
{
	t_philo	**philo_array;
	int		i;

	philo_array = malloc(sizeof(t_philo *) * rules->n_philo);
	if (!philo_array)
		return (handle_events_error(events, rules));
	i = -1;
	while (++i < rules->n_philo)
	{
		philo_array[i] = init_philo(rules, events, i + 1);
		if (!philo_array[i])
		{
			free_philo_array(philo_array, i + 1);
			return (handle_events_error(events, rules));
		}
	}
	return (philo_array);
}

void	unlink_sem(void)
{
	sem_unlink("write");
	sem_unlink("forks");
	sem_unlink("end_simu");
	sem_unlink("eated_enough");
}

t_events	*init_events(t_rules *rules)
{
	t_events	*events;

	events = NULL;
	events = malloc(sizeof(t_events));
	if (!events)
		return (handle_events_error(events, rules));
	events->n_as_ated_enough = 0;
	events->init_timestamp.tv_sec = 0;
	events->init_timestamp.tv_usec = 0;
	unlink_sem();
	events->write_something = sem_open("write", O_CREAT, S_IRWXG, 1);
	if (events->write_something == SEM_FAILED)
		return (handle_events_error(events, rules));
	events->fork_dispo = sem_open("forks", O_CREAT, S_IRWXG, rules->n_philo);
	if (events->fork_dispo == SEM_FAILED)
		return (handle_events_error(events, rules));
	events->end_simu = sem_open("end_simu", O_CREAT, S_IRWXG, 0);
	if (events->end_simu == SEM_FAILED)
		return (handle_events_error(events, rules));
	events->eated_enough = sem_open("eated_enough", O_CREAT, S_IRWXG, 0);
	if (events->eated_enough == SEM_FAILED)
		return (handle_events_error(events, rules));
	return (events);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = NULL;
	if (!(argc == 5 || argc == 6))
		return (handle_rules_error(rules));
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	if (ft_atoi(argv[1], &rules->n_philo) != 0)
		return (handle_rules_error(rules));
	if (ft_atoi(argv[2], &rules->t_die) != 0)
		return (handle_rules_error(rules));
	if (ft_atoi(argv[3], &rules->t_eat) != 0)
		return (handle_rules_error(rules));
	if (ft_atoi(argv[4], &rules->t_sleep) != 0)
		return (handle_rules_error(rules));
	rules->t_must_eat = -1;
	if (argc == 6)
		if (ft_atoi(argv[5], &rules->t_must_eat) != 0)
			return (handle_rules_error(rules));
	return (rules);
}
