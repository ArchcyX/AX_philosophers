/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:05:07 by alermi            #+#    #+#             */
/*   Updated: 2025/04/28 16:08:14 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_imp(void **allocate)
{
	if (*allocate)
		free(*allocate);
	*allocate = NULL;
}

void	free_matris(void **matris)
{
	int	i;

	i = -1;
	while (matris[++i])
		free(matris[i]);
	matris = NULL;
}

void	end_simulation(t_rules	*rule)
{
	register int	i;

	i = -1;
	while (++i < 4)
	{
		if (pthread_mutex_unlock(&rule->fork[i]))
			pthread_mutex_destroy(&rule->fork[i]);
		if (pthread_mutex_unlock(&rule->philos[i].death_control))
			pthread_mutex_destroy(&rule->philos[i].death_control);
	}
	if (pthread_mutex_unlock(&rule->mutex.start_control))
		pthread_mutex_destroy(&rule->mutex.start_control);
	if (pthread_mutex_unlock(&rule->mutex.end_control))
		pthread_mutex_destroy(&rule->mutex.end_control);
	if (pthread_mutex_unlock(&rule->mutex.total_eaten_meal))
		pthread_mutex_destroy(&rule->mutex.total_eaten_meal);
	free_imp((void *)&rule->fork);
	free_imp((void *)&rule->philos);
}