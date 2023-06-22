/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:59:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/12 10:50:08 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork_dispo_mutexes(t_events *events, t_rules *rules)
{
	int	i;

	i = -1;
	events->fork_dispo = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!events->fork_dispo)
	{
		pthread_mutex_destroy(&events->write_something);
		return (1);
	}
	while (++i < rules->n_philo)
	{
		if (pthread_mutex_init(&events->fork_dispo[i], NULL) != 0)
		{
			pthread_mutex_destroy(&events->write_something);
			destroy_mutex_array(events->fork_dispo, i + 1);
			return (1);
		}
	}
	return (0);
}

t_philo	*init_philo(t_rules *rules, t_events *events, int n)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->rules = rules;
	philo->events = events;
	philo->number = n;
	philo->str_number = ft_itoa(n);
	if (!philo->str_number)
	{
		free(philo);
		return (NULL);
	}
	philo->left_fork = philo->number - 1;
	if (philo->rules->n_philo == philo->number)
		philo->right_fork = 0;
	else
		philo->right_fork = philo->number;
	philo->as_eated = 0;
	philo->last_meal = -1;
	return (philo);
}

t_philo	**init_philo_array(t_rules *rules, t_events *events)
{
	t_philo	**philo_array;
	int		i;

	philo_array = malloc(sizeof(t_philo *) * rules->n_philo);
	if (!philo_array)
	{
		pthread_mutex_destroy(&events->write_something);
		destroy_mutex_array(events->fork_dispo, rules->n_philo);
		return (handle_events_error(events, rules));
	}
	i = -1;
	while (++i < rules->n_philo)
	{
		philo_array[i] = init_philo(rules, events, i + 1);
		if (!philo_array[i])
		{
			free_philo_array(philo_array, i + 1);
			pthread_mutex_destroy(&events->write_something);
			destroy_mutex_array(events->fork_dispo, rules->n_philo);
			return (handle_events_error(events, rules));
		}
	}
	return (philo_array);
}

t_events	*init_events(t_rules *rules)
{
	t_events	*events;

	events = NULL;
	events = malloc(sizeof(t_events));
	if (!events)
		return (handle_events_error(events, rules));
	events->end = 0;
	events->n_as_ated_enough = 0;
	events->init_timestamp.tv_sec = 0;
	events->init_timestamp.tv_usec = 0;
	if (pthread_mutex_init(&events->write_something, NULL) != 0)
		return (handle_events_error(events, rules));
	if (init_fork_dispo_mutexes(events, rules) != 0)
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
	{
		printf("System error: %d\n", errno);
		return (NULL);
	}
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
