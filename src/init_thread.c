/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:28:36 by alermi            #+#    #+#             */
/*   Updated: 2025/04/27 12:30:05 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

extern  __inline__  int
	creat_philo(t_rules *rule, int i)
{
	t_philo	philosophers;

	memset(&philosophers, 0, sizeof(t_philo));
	rule->philos[i].philo_id = i;
	rule->philos[i].rules = rule;
	if (pthread_create(&(rule->philos[i].id), 0, simulation_init,
	 (void *)&rule->philos[i]) != 0)
		return (1);
	return (0);
}

int    creat_enviroment(t_rules *head)
{
	int counter;

	counter = -1;
	head->philos = (t_philo *)malloc(head->count_philo * sizeof(t_philo));
	head->fork = malloc(head->count_philo * sizeof(pthread_mutex_t));
	if (!head->philos || !head->fork)
		return (put_error("=> Malloc Error\n"));
	while (++counter < head->count_philo)
		if (pthread_mutex_init(&head->fork[counter], NULL) == -1)
			return (1);
	counter = -1;
//S
	while (++counter < head->count_philo)
		if (creat_philo(head, counter))
			return (1);
	pthread_mutex_lock(&head->mutex);
	head->start = get_time_ms((void *)head);
	head->game_start = 1;
	pthread_mutex_unlock(&head->mutex);
	return (0);
}

int fork_init(t_rules *rule)
{
	int i;
	int next;

	i = 0;
	while (i < rule->count_philo)
	{
		rule->philos[i].r_fork = &rule->fork[i];
		next = (i + 1) % rule->count_philo;
		rule->philos[i].l_fork = &rule->fork[next];
		i++;
	}
	return (0);
}
