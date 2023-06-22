/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:24:49 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/05 16:11:50 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_actual_timestamp(t_events *events)
{
	struct timeval	new_time;
	int				seconds;
	int				micro_seconds;

	if (gettimeofday(&new_time, NULL) != 0)
		return (-1);
	seconds = new_time.tv_sec - events->init_timestamp.tv_sec;
	if (new_time.tv_usec < events->init_timestamp.tv_usec)
	{
		seconds -= 1;
		micro_seconds
			= 1000000 - events->init_timestamp.tv_usec + new_time.tv_usec;
	}
	else
		micro_seconds = new_time.tv_usec - events->init_timestamp.tv_usec;
	return ((seconds * 1000) + micro_seconds / 1000);
}

void	write_message_type(int msg)
{
	if (msg == DEAD)
		write(1, " died\n", 6);
	else if (msg == EAT)
		write(1, " is eating\n", 11);
	else if (msg == SLEEP)
		write(1, " is sleeping\n", 13);
	else if (msg == THINK)
		write(1, " is thinking\n", 13);
	else if (msg == TAKE)
		write(1, " has taken a fork\n", 18);
}

int	write_something(t_philo *philo, int msg)
{
	char	*timestamp;

	if (philo->events->end == 0 || msg == DEAD)
	{
		pthread_mutex_lock(&philo->events->write_something);
		timestamp = ft_itoa(get_actual_timestamp(philo->events));
		if (!timestamp)
		{
			pthread_mutex_unlock(&philo->events->write_something);
			return (1);
		}
		write(1, timestamp, ft_strlen(timestamp));
		write(1, " ms ", 4);
		write(1, philo->str_number, ft_strlen(philo->str_number));
		write_message_type(msg);
		pthread_mutex_unlock(&philo->events->write_something);
		free(timestamp);
	}
	return (0);
}
