/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:05:07 by alermi            #+#    #+#             */
/*   Updated: 2025/04/21 20:05:20 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_imp(void *allocate)
{
	if (allocate)
		free(allocate);
	allocate = NULL;
}

void	free_matris(void **matris)
{
	int	i;
	
	i = -1;
	while (matris[++i])
		free(matris[i]);
	matris = NULL;
}
