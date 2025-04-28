/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:31:24 by alermi            #+#    #+#             */
/*   Updated: 2025/04/28 16:09:34 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>

void	acting(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mutex.total_eaten_meal);
	pthread_mutex_lock(philo->l_fork);
	p_info(philo, "Sol Çatalı Aldı");
	pthread_mutex_lock(philo->r_fork);
	p_info(philo, "Sağ Çatalı Aldı");
	ft_sleep(philo->rules->time_to_eat, philo->rules);
	p_info(philo, "->Yemeği Yedi");
	pthread_mutex_lock(&philo->death_control);
	philo->kill_time = get_time() + philo->rules->time_to_die;
	pthread_mutex_unlock(&philo->death_control);
	pthread_mutex_unlock(philo->l_fork);
	p_info(philo, "Sol Çatalı Bıraktı");
	pthread_mutex_unlock(philo->r_fork);
	p_info(philo, "Sağ Çatalı Bıraktı");
	philo->eaten_meal++;
	pthread_mutex_lock(&philo->rules->mutex.total_eaten_meal);
	philo->rules->total_eaten_meal++;
	pthread_mutex_unlock(&philo->rules->mutex.total_eaten_meal);
	p_info(philo, "Sleeping");
	ft_sleep(philo->rules->time_to_sleep, philo->rules);
	p_info(philo, "Thinking");
}

extern __inline__	void
    *state_controller(t_philo *philo)
{
	if (philo->philo_id % 2 == 1);
		usleep(2);
	pthread_mutex_lock(&philo->rules->mutex.end_control);
	while (!philo->rules->end)
	{
		pthread_mutex_unlock(&philo->rules->mutex.end_control);

		if ((philo->rules->must_eat == philo->eaten_meal) && \
			!!philo->rules->must_eat)
			return ((void *)0);
		pthread_mutex_lock(&philo->rules->mutex.total_eaten_meal);
		if ((philo->rules->total_eaten_meal \
			/ philo->rules->count_philo) \
			== philo->eaten_meal)
			acting(philo);
		else
			pthread_mutex_unlock(&philo->rules->mutex.total_eaten_meal);
		pthread_mutex_lock(&philo->rules->mutex.end_control);
	}
	pthread_mutex_unlock(&philo->rules->mutex.end_control);
}

void	*simulation_init(void *member)
{
	t_rules			*rule;
	t_philo			*philo;

	philo = (t_philo *)member;
	rule = philo->rules;

	while (1)
	{
		pthread_mutex_lock(&rule->mutex.start_control);
		if (rule->game_start == 1)
			break ;
		pthread_mutex_unlock(&rule->mutex.start_control);
	}
	pthread_mutex_unlock(&rule->mutex.start_control);
	philo->kill_time = get_time() + rule->time_to_die;
	state_controller(philo);
}
