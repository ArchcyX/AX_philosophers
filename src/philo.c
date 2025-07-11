/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:01:16 by alermi            #+#    #+#             */
/*   Updated: 2025/07/06 01:53:30 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern __inline__ int
	init_values(int argc, char **argv, t_rules *rule)
{
	rule->count_philo = ax_atoi(argv[1]);
	rule->time_to_die = ax_atoi(argv[2]);
	rule->time_to_eat = ax_atoi(argv[3]);
	rule->time_to_sleep = ax_atoi(argv[4]);
	if (argc == 6)
		rule->must_eat = ax_atoi(argv[5]);
	else
		rule->must_eat = -1;
	if (rule->count_philo <= 0
		|| rule->time_to_die <= 0
		|| rule->time_to_eat <= 0
		|| rule->time_to_sleep <= 0
		|| rule->must_eat == 0)
		return (1);
	return (0);
}

extern __inline__ void
	death_or_success(t_rules *rule, int i)
{
	int	current_time;

	pthread_mutex_lock(&rule->mutex.total_eaten_meal);
	if (rule->total_eaten_meal / rule->count_philo == rule->must_eat)
		printf("=Success=");
	else
	{
		pthread_mutex_lock(&rule->mutex.end_control);
		rule->end = 1;
		pthread_mutex_unlock(&rule->mutex.end_control);
		current_time = get_time_ms((void *)rule);
		ft_sleep(1, rule);
		printf("%d  %d %s\n", current_time, i, "is Death");
	}
	pthread_mutex_unlock(&rule->mutex.total_eaten_meal);
}

extern	__inline__ void
	death_controller(t_rules	*rule)
{
	register int	i;

	pthread_mutex_lock(&rule->mutex.end_control);
	while (!rule->end)
	{
		pthread_mutex_unlock(&rule->mutex.end_control);
		i = -1;
		while (++i < rule->count_philo)
		{
			pthread_mutex_lock(&rule->philos[i].kill_control);
			if (rule->philos[i].kill_time < get_time())
			{
				pthread_mutex_unlock(&rule->philos[i].kill_control);
				death_or_success(rule, i);
				pthread_mutex_lock(&rule->mutex.end_control);
				rule->end = 1;
				pthread_mutex_unlock(&rule->mutex.end_control);
				break ;
			}
			pthread_mutex_unlock(&rule->philos[i].kill_control);
		}
		pthread_mutex_lock(&rule->mutex.end_control);
	}
	pthread_mutex_unlock(&rule->mutex.end_control);
}

extern	__inline__	int
	single_philo(t_rules *rule)
{
	creat_enviroment(rule);
	ft_sleep(rule->time_to_die, rule);
	p_info(&rule->philos[0], "is Death");
	pthread_mutex_lock(&rule->mutex.end_control);
	rule->end = 1;
	pthread_mutex_unlock(&rule->mutex.end_control);
	death_controller(rule);
	pthread_join(rule->philos[0].id, NULL);
	pthread_mutex_destroy(&rule->fork[0]);
	pthread_mutex_destroy(&rule->philos[0].kill_control);
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules				rule;
	register int		i;

	i = 0;
	memset(&rule, 0, sizeof(t_rules));
	if (argc == 5 || argc == 6)
	{
		if (init_values(argc, argv, &rule))
			return (put_error("\nError!!\n"));
		if (rule.count_philo == 1)
			return (single_philo(&rule));
		if (creat_enviroment(&rule))
		{
			pthread_mutex_lock(&rule.mutex.end_control);
			rule.end = 1;
			pthread_mutex_unlock(&rule.mutex.end_control);
		}
	}
	else
		return (put_error("Error!!"));
	death_controller(&rule);
	i = -1;
	while (++i < rule.count_philo)
		pthread_join(rule.philos[i].id, NULL);
	end_simulation(&rule);
}
