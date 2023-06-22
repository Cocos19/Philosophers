/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:23:05 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/12 10:46:25 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_array(pthread_mutex_t *t_array, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&t_array[i]);
	free(t_array);
}

void	*handle_events_error(t_events *events, t_rules *rules)
{
	printf("System error: %d\n", errno);
	if (events)
		free(events);
	free(rules);
	return (NULL);
}

void	*handle_rules_error(t_rules *rules)
{
	printf("Wrong argument format\n");
	if (rules)
		free(rules);
	return (NULL);
}

void	free_all(t_rules *rul, t_events *ev, t_philo **ph, pthread_t *th)
{
	if (th)
		free(th);
	if (ph)
	{
		free_philo_array(ph, rul->n_philo);
	}
	if (ev)
	{
		pthread_mutex_destroy(&ev->write_something);
		destroy_mutex_array(ev->fork_dispo, rul->n_philo);
		free(ev);
	}
	if (rul)
		free(rul);
}

void	free_philo_array(t_philo **philo_array, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (philo_array[i]->str_number)
			free(philo_array[i]->str_number);
		free(philo_array[i]);
	}
	free(philo_array);
}
