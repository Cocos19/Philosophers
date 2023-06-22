/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:46:00 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/09 20:33:44 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	close_and_unlink_sem(t_events *events)
{
	sem_close(events->write_something);
	sem_unlink("write");
	sem_close(events->fork_dispo);
	sem_unlink("forks");
	sem_close(events->fork_dispo);
	sem_unlink("end_simu");
	sem_close(events->fork_dispo);
	sem_unlink("eated_enough");
}

void	free_all(t_rules *rul, t_events *ev, t_philo **ph)
{
	if (ph)
		free_philo_array(ph, rul->n_philo);
	if (ev)
	{
		close_and_unlink_sem(ev);
		free(ev);
	}
	if (rul)
		free(rul);
}

void	*handle_events_error(t_events *events, t_rules *rules)
{
	printf("System error: %d\n", errno);
	if (events)
	{
		close_and_unlink_sem(events);
		free(events);
	}
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
