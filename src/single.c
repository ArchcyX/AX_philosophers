/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:05:59 by alermi            #+#    #+#             */
/*   Updated: 2025/07/14 01:07:14 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	single_philo(t_rules *rule)
{
	creat_enviroment(rule);
	ft_sleep(rule->time_to_die, rule);
	p_info(&rule->philos[0], "is Death");
	pthread_mutex_lock(&rule->mutex.end_control);
	rule->end = 1;
	pthread_mutex_unlock(&rule->mutex.end_control);
	death_controller(rule);
	pthread_join(rule->philos[0].id, NULL);
	pthread_mutex_destroy(&rule->philos[0].kill_control);
	free_imp((void *)&rule->fork);
	free_imp((void *)&rule->philos);
	return (1);
}

void	singler_philo(t_philo *philo)
{
	static int	counter = 0;

	pthread_mutex_unlock(&philo->rules->mutex.total_eaten_meal);
	if (counter == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		p_info(philo, "Sol Çatalı Aldı");
		counter++;
	}
}
