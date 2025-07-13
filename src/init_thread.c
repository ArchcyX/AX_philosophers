/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:28:36 by alermi            #+#    #+#             */
/*   Updated: 2025/07/14 01:49:37 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

extern __inline__ int
	creat_philo(t_rules *rule, int i)
{
	memset(&(rule->philos[i]), 0, sizeof(t_philo));
	rule->philos[i].philo_id = i + 1;
	rule->philos[i].rules = rule;
	rule->philos[i].kill_time = get_time() + rule->time_to_die;
	if (pthread_mutex_init(&rule->philos[i].kill_control, NULL))
		return (put_error("Mutex Not Created"));
	if (pthread_create(&(rule->philos[i].id), 0, simulation_init,
			(void *)&rule->philos[i]) != 0)
		return (put_error("Threads Not Created"));
	return (0);
}

extern __inline__ int
	create_mutexes(t_rules *rule)
{
	int	counter;

	counter = -1;
	while (++counter < rule->count_philo)
		if (pthread_mutex_init(&rule->fork[counter], NULL) == -1)
			return (1);
	if (pthread_mutex_init(&rule->mutex.start_control, NULL)
		|| pthread_mutex_init(&rule->mutex.end_control, NULL)
		|| pthread_mutex_init(&rule->mutex.total_eaten_meal, NULL))
		return (1);
	return (0);
}

extern __inline__	void
	fork_init(t_rules *rule)
{
	register int	i;
	int				next;

	i = 0;
	while (i < rule->count_philo)
	{
		rule->philos[i].r_fork = &rule->fork[i];
		next = (i + 1) % rule->count_philo;
		rule->philos[i].l_fork = &rule->fork[next];
		i++;
	}
}

int	creat_enviroment(t_rules *head)
{
	int	counter;

	counter = -1;
	head->philos = (t_philo *)malloc(head->count_philo * sizeof(t_philo));
	head->fork = malloc(head->count_philo * sizeof(pthread_mutex_t));
	if (!head->philos || !head->fork)
		return (put_error("=> Malloc Error\n"));
	if (create_mutexes(head))
		return (put_error("=> Mutex not Created"));
	while (++counter < head->count_philo)
		if (creat_philo(head, counter))
			return (1);
	fork_init(head);
	pthread_mutex_lock(&head->mutex.start_control);
	head->start = get_time_ms((void *)head);
	head->game_start = 1;
	pthread_mutex_unlock(&head->mutex.start_control);
	return (0);
}
