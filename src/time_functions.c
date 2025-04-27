/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:12:32 by alermi            #+#    #+#             */
/*   Updated: 2025/04/27 00:54:46 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>

int	get_time(void *main_struct)
{
	struct timeval	tv;
	t_rules			*rule;

	rule = (t_rules *)main_struct;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec - rule->start);
}

int	get_time_ms(void *main_struct)
{
	struct	timeval	tv;
	t_rules			*rule;
	
	rule = (t_rules *)main_struct;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - rule->start);
}

void	ft_sleep(int milisecond, t_rules *rule)
{
	int	start_time;
	int	current_time;

	start_time = get_time_ms(rule);
	current_time = start_time;
	while (start_time - current_time < milisecond)
	{	
		current_time = start_time;
		usleep(100);
	}
}