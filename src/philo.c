/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:01:16 by alermi            #+#    #+#             */
/*   Updated: 2025/04/28 17:51:20 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <string.h>

extern __inline__ void 
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
}

extern	__inline__ void
	deat_controller(t_rules	*rule)
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
				p_info(&rule->philos[i], "Philos is Death");
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

int main(int argc, char **argv)
{
	t_rules	rule;
	int		i;

	i = 0;
	memset(&rule, 0, sizeof(t_rules));
	if (argc == 5 || argc == 6)
    {
		init_values(argc, argv, &rule);
		if (creat_enviroment(&rule))
			rule.end = 1;
	}
    else
		return (put_error("Error!!"));
	deat_controller(&rule);
	i = -1;
	while (++i < rule.count_philo)
		pthread_join(rule.philos[i].id, NULL);
	end_simulation(&rule);
	return (0);
}

// creat the closing all // TODO: CREATE A FUNCTION TO FREE ALL SHIT
// waiting