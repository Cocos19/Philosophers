/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:07:57 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/10 10:46:01 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_n_time(t_philo *philo, int n)
{
	int	end_timestamp;
	int	actual_timestamp;

	actual_timestamp = get_actual_timestamp(philo->events);
	if (actual_timestamp == -1)
		return (1);
	if (n == SLEEP)
		end_timestamp = actual_timestamp + philo->rules->t_sleep;
	else
		end_timestamp = actual_timestamp + philo->rules->t_eat;
	while (actual_timestamp < end_timestamp)
	{
		usleep(100);
		actual_timestamp = get_actual_timestamp(philo->events);
		if (actual_timestamp == -1)
			return (1);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->events->fork_dispo[philo->left_fork]);
	write_something((t_philo *)philo, TAKE);
	if (philo->rules->n_philo != 1)
	{
		pthread_mutex_lock(&philo->events->fork_dispo[philo->right_fork]);
		write_something((t_philo *)philo, TAKE);
	}
	else
	{
		while (philo->events->end == 0)
			usleep(100);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->events->fork_dispo[philo->left_fork]);
	pthread_mutex_unlock(&philo->events->fork_dispo[philo->right_fork]);
}

int	eat(t_philo *philo)
{
	philo->last_meal = get_actual_timestamp(philo->events);
	if (philo->last_meal == -1)
	{
		release_forks(philo);
		return (1);
	}
	if (wait_n_time(philo, EAT) != 0)
	{
		release_forks(philo);
		return (1);
	}
	if (philo->as_eated != -1)
		++philo->as_eated;
	release_forks(philo);
	return (0);
}

void	*start_routine(void *philo)
{
	((t_philo *)philo)->last_meal
		= get_actual_timestamp(((t_philo *)philo)->events);
	if (((t_philo *)philo)->last_meal == -1)
		return (NULL);
	while (((t_philo *)philo)->events->end == 0)
	{
		take_forks((t_philo *)philo);
		write_something(philo, EAT);
		if (eat((t_philo *)philo) != 0)
			return (NULL);
		write_something((t_philo *)philo, SLEEP);
		if (wait_n_time((t_philo *)philo, SLEEP) != 0)
			return (NULL);
		write_something((t_philo *)philo, THINK);
	}
	return (NULL);
}
