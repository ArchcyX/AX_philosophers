/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:01:16 by alermi            #+#    #+#             */
/*   Updated: 2025/04/27 17:53:50 by alermi           ###   ########.fr       */
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
			return (put_error("Error!!"));
		if (fork_init(&rule) == 0)
			put_error("{<============Program Başlatıldı=======>}");
		usleep(1000 * 1000);// EDİT THİS
	}
    else
		return (put_error("Error!!"));
	i = -1;
	while (++i < rule.count_philo)
		pthread_join(rule.philos[i].id, NULL);
	i = -1;	
	while (++i < 4)
		if (pthread_mutex_destroy(&rule.fork[i]) == 0);
	free_imp(rule.fork);
	free_imp(rule.philos);
	return (0);
}

// creat the closing all
// waiting