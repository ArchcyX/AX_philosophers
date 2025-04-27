/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:31:24 by alermi            #+#    #+#             */
/*   Updated: 2025/04/27 18:33:34 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>

void	p_eat(t_philo *philo)
{
	int		eat_started;
	int		current_time;
	
	// pthread_mutex_unlock(&philo->rules->mutex.tem_nop);
	eat_started = get_time_ms((void *)philo->rules);
	if (pthread_mutex_lock(philo->l_fork))
		p_info(philo, "Sol Çatalı Aldı");
	if (pthread_mutex_lock(philo->r_fork))
		p_info(philo, "Sağ Çatalı Aldı");
	while (current_time - eat_started < philo->rules->time_to_eat)
		current_time = get_time_ms((void *)philo->rules);
	p_info(philo, "->Yemeği Yedi");
	pthread_mutex_unlock(philo->l_fork);
	p_info(philo, "Sol Çatalı Bıraktı");
	pthread_mutex_unlock(philo->r_fork);
	p_info(philo, "Sağ Çatalı Bıraktı");
	philo->eaten_meal++;
	// pthread_mutex_lock(&philo->rules->mutex.tem_nop);
	philo->rules->total_eaten_meal++;
	// pthread_mutex_unlock(&philo->rules->mutex.tem_nop);
}

extern __inline__	void
    *state_selector(t_philo *philo)
{
	if (philo->philo_id % 2 == 1);
		usleep(2);
	pthread_mutex_lock(&philo->rules->mutex); // TODO: CUSTOM MUTEX FOR ->END
	while (!philo->rules->end)
	{
		pthread_mutex_unlock(&philo->rules->mutex); // TODO: CUSTOM MUTEX FOR ->END

		if ((philo->rules->must_eat == philo->eaten_meal) && \
			!!philo->rules->must_eat)
			return ((void *)0);

		// TODO: MUTEX FOR ->number_of_philos_AND_total_eaten_meal JUST A SINGLE MUTEXT IS ENOUGH
		// pthread_mutex_lock(&philo->rules->mutex.tem_nop);
		if ((philo->rules->total_eaten_meal \
			/ philo->rules->number_of_philos) \
			== philo->eaten_meal)
			p_eat(philo); // UNLOCK THE tem_nop INSIDE THIS FUNCTION;
		else
			// pthread_mutex_unlock(&philo->rules->mutex.tem_nop);

		pthread_mutex_lock(&philo->rules->mutex); // TODO: CUSTOM MUTEX FOR ->END
	}
	pthread_mutex_unlock(&philo->rules->mutex); // TODO: CUSTOM MUTEX FOR ->END
}

void	*simulation_init(void *member)
{
	t_rules			*rule;
	t_philo			*philo;

	philo = (t_philo *)member;
	rule = philo->rules;

	printf("\n%p\n", philo->rules);
	while (1)
	{
		pthread_mutex_lock(&rule->mutex);
		if (rule->game_start == 1)
			break;
		pthread_mutex_unlock(&rule->mutex);
	}
	pthread_mutex_unlock(&rule->mutex);
	state_selector(philo);
}
