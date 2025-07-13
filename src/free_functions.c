/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:05:07 by alermi            #+#    #+#             */
/*   Updated: 2025/07/14 01:47:17 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

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
		pthread_mutex_destroy(&rule->fork[i]);
		pthread_mutex_destroy(&rule->philos[i].kill_control);
	}
	pthread_mutex_destroy(&rule->mutex.start_control);
	pthread_mutex_destroy(&rule->mutex.end_control);
	pthread_mutex_destroy(&rule->mutex.total_eaten_meal);
	free_imp((void *)&rule->fork);
	free_imp((void *)&rule->philos);
}
