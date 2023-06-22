/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:01:46 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/10 15:56:08 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_message(t_philo *philo, int *time, int *msg)
{
	char	*timestamp;

	timestamp = ft_itoa(*time);
	if (!timestamp)
		exit(EXIT_FAILURE);
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ms ", 4);
	write(1, philo->str_number, philo->str_number_len);
	if (*msg == DEAD)
		write(1, " died\n", 6);
	else if (*msg == EAT)
		write(1, " is eating\n", 11);
	else if (*msg == SLEEP)
		write(1, " is sleeping\n", 13);
	else if (*msg == THINK)
		write(1, " is thinking\n", 13);
	else if (*msg == TAKE)
		write(1, " has taken a fork\n", 18);
	free(timestamp);
}

int	write_something(t_philo *philo, int msg)
{
	int		time;

	sem_wait(philo->events->write_something);
	if (msg != END)
	{
		time = get_time(philo->events);
		write_message(philo, &time, &msg);
	}
	if (!(msg == DEAD || msg == END))
		sem_post(philo->events->write_something);
	if (msg == EAT)
	{
		philo->last_meal = time;
		if (++philo->as_eated == philo->rules->t_must_eat)
			sem_post(philo->events->eated_enough);
	}
	return (0);
}

int	get_time(t_events *events)
{
	struct timeval	new_time;

	if (gettimeofday(&new_time, NULL) != 0)
		return (-1);
	if (new_time.tv_usec < events->init_timestamp.tv_usec)
		return (((new_time.tv_sec - events->init_timestamp.tv_sec - 1) * 1000)
			+ ((1000000 - events->init_timestamp.tv_usec + new_time.tv_usec)
				/ 1000));
	else
		return (((new_time.tv_sec - events->init_timestamp.tv_sec) * 1000)
			+ ((new_time.tv_usec - events->init_timestamp.tv_usec) / 1000));
}
