/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:34:10 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/10 10:55:36 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_eaters(void	*philo)
{
	while (((t_philo *)philo)->events->n_as_ated_enough
		< ((t_philo *)philo)->rules->n_philo)
	{
		sem_wait(((t_philo *)philo)->events->eated_enough);
		++((t_philo *)philo)->events->n_as_ated_enough;
	}
	write_something(((t_philo *)philo), END);
	sem_post(((t_philo *)philo)->events->end_simu);
	return (NULL);
}

void	send_sigkill(t_philo **philosophers)
{
	int	i;

	i = -1;
	while (++i < philosophers[0]->rules->n_philo)
		kill (philosophers[i]->pid, SIGKILL);
}

int	create_forks(t_philo **ph, int i)
{
	while (i < ph[0]->rules->n_philo)
	{
		ph[i]->pid = fork();
		if (ph[i]->pid == -1)
			return (1);
		if (ph[i]->pid == 0)
			philo_routine(ph[i]);
		i += 2;
	}
	return (0);
}

int	launch_philo(t_philo **ph)
{
	int			i;
	pthread_t	check_eating_philos;

	i = -1;
	if (gettimeofday(&ph[0]->events->init_timestamp, NULL) != 0)
		return (1);
	if (pthread_create(&check_eating_philos, NULL, &check_eaters, ph[0]) != 0)
		return (1);
	if (pthread_detach(check_eating_philos) != 0)
		return (1);
	if (create_forks(ph, 0) != 0)
		return (1);
	usleep(100);
	if (create_forks(ph, 1) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules		*rules;
	t_events	*events;
	t_philo		**philosophers;

	rules = init_rules(argc, argv);
	if (!rules)
		return (1);
	else if (rules->n_philo == 0)
		return (0);
	events = init_events(rules);
	if (!events)
		return (1);
	philosophers = init_philo_array(rules, events);
	if (!philosophers)
		return (1);
	if (launch_philo(philosophers) != 0)
		sem_post(philosophers[0]->events->end_simu);
	sem_wait(events->end_simu);
	send_sigkill(philosophers);
	free_all(rules, events, philosophers);
	return (0);
}
