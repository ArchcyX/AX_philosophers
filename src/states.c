/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:31:24 by alermi            #+#    #+#             */
/*   Updated: 2025/04/23 18:56:16 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void    *state_selector(void *main_struct)
{
	t_rules	*rule;

	rule = (t_rules *)main_struct;
	pthread_mutex_lock(&rule->mutex);
	rule->created_philo++;
	while (rule->created_philo < rule->count_philo)
	{
		pthread_mutex_unlock(&rule->mutex);
		usleep(1000);
		pthread_mutex_lock(&rule->mutex);
	}
	printf("aynen hepsi oluşturuldu");
}
