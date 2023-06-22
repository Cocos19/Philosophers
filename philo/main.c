/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:55:07 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/10 15:59:01 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*init_philo_threads_array(int array_size)
{
	pthread_t	*result;

	result = malloc(sizeof(pthread_t) * array_size);
	if (!result)
		return (NULL);
	return (result);
}

void	check_philo(t_philo **ph, t_events *events, t_rules *rules)
{
	int	i;
	int	actual_time;

	i = -1;
	actual_time = get_actual_timestamp(events);
	if (actual_time == -1)
		events->end = 1;
	while (++i < rules->n_philo && events->end == 0)
	{
		if (ph[i]->as_eated != -1)
		{
			if (ph[i]->as_eated == rules->t_must_eat)
			{
				ph[i]->as_eated = -1;
				if (++events->n_as_ated_enough == rules->n_philo)
					events->end = 1;
			}
		}
		if (ph[i]->last_meal + rules->t_die <= actual_time && events->end == 0)
		{
			events->end = 1;
			write_something(ph[i], DEAD);
		}
	}
}

int	create_threads(t_philo **ph, pthread_t *th, int i)
{
	while (i < ph[0]->rules->n_philo)
	{
		if (pthread_create(&th[i], NULL, &start_routine, ph[i]) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

int	execute_threads(t_philo **philo_array, pthread_t *philo_threads)
{
	int	i;

	if (gettimeofday(&philo_array[0]->events->init_timestamp, NULL) != 0)
		return (1);
	if (create_threads(philo_array, philo_threads, 0) != 0)
		return (1);
	usleep(100);
	if (create_threads(philo_array, philo_threads, 1) != 0)
		return (1);
	while (philo_array[0]->events->end == 0)
		check_philo(philo_array, philo_array[0]->events, philo_array[0]->rules);
	i = -1;
	while (++i < philo_array[0]->rules->n_philo)
		if (pthread_join(philo_threads[i], NULL) != 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules		*rules;
	t_events	*events;
	t_philo		**philosophers;
	pthread_t	*philo_thread;

	rules = init_rules(argc, argv);
	if (!rules || rules->n_philo == 0 || rules->t_must_eat == 0)
		return (1);
	events = init_events(rules);
	if (!events)
		return (1);
	philosophers = init_philo_array(rules, events);
	if (!philosophers)
		return (1);
	philo_thread = init_philo_threads_array(rules->n_philo);
	if (!philo_thread)
	{
		free_all(rules, events, philosophers, philo_thread);
		return (1);
	}
	execute_threads(philosophers, philo_thread);
	free_all(rules, events, philosophers, philo_thread);
	return (0);
}
