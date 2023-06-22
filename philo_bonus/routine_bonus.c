/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:44 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/09 20:51:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	wait_n_time(t_philo *philo, int n)
{
	int	end_timestamp;
	int	actual_timestamp;

	actual_timestamp = get_time(philo->events);
	if (actual_timestamp == -1)
		exit (EXIT_FAILURE);
	if (n == SLEEP)
		end_timestamp = actual_timestamp + philo->rules->t_sleep;
	else
		end_timestamp = actual_timestamp + philo->rules->t_eat;
	while (actual_timestamp < end_timestamp)
	{
		usleep(100);
		actual_timestamp = get_time(philo->events);
		if (actual_timestamp == -1)
			return (EXIT_FAILURE);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	if (sem_wait(philo->events->fork_dispo) != 0)
		exit(EXIT_FAILURE);
	write_something((t_philo *)philo, TAKE);
	if (sem_wait(philo->events->fork_dispo) != 0)
		exit(EXIT_FAILURE);
	write_something((t_philo *)philo, TAKE);
}

void	release_forks(t_philo *philo)
{
	if (sem_post(philo->events->fork_dispo) != 0)
		exit(EXIT_FAILURE);
	if (sem_post(philo->events->fork_dispo) != 0)
		exit(EXIT_FAILURE);
}

void	*check_eating_status(void *philo)
{
	int	actual_time;

	((t_philo *)philo)->last_meal = get_time(((t_philo *)philo)->events);
	while (1)
	{
		actual_time = get_time(((t_philo *)philo)->events);
		if (actual_time == -1)
			sem_post(((t_philo *)philo)->events->end_simu);
		if (((t_philo *)philo)->last_meal + ((t_philo *)philo)->rules->t_die
			<= actual_time)
		{
			write_something((t_philo *)philo, DEAD);
			sem_post(((t_philo *)philo)->events->end_simu);
		}
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	pthread_t	monitoring;

	if (pthread_create(&monitoring, NULL, &check_eating_status, philo) != 0)
		return (NULL);
	while (1)
	{
		take_forks(philo);
		write_something(philo, EAT);
		wait_n_time(philo, EAT);
		release_forks(philo);
		write_something(philo, SLEEP);
		wait_n_time(philo, SLEEP);
		write_something(philo, THINK);
	}
}
