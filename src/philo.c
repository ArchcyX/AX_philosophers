/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:01:16 by alermi            #+#    #+#             */
/*   Updated: 2025/04/23 18:53:10 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <string.h>

extern __inline__ void
	init_values(int argc, char **argv, t_rules *rule)
{
	int		count;

	count = 0;
	while (++count < argc - 1)
		((int *)rule)[count - 1] =  ax_atoi(argv[count]);
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
			put_error("Okey");
		i = -1;
		while (++i < 4)
			if (pthread_mutex_destroy(&rule.fork[i]) == 0);
		usleep(1000 * 1000);
	}
    else
		return (put_error("Error!!"));
	if (pthread_mutex_destroy(&rule.mutex) == 0);
	i = -1;
	while (++i < rule.count_philo)
		pthread_join(rule.philos[i].id, NULL);
	free_imp(rule.fork);
	free_imp(rule.philos);
	return (0);
}
