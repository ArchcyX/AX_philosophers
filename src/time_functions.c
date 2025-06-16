/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:12:32 by alermi            #+#    #+#             */
/*   Updated: 2025/06/16 17:34:37 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	get_time_ms(void *main_struct)
{
	struct timeval	tv;
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
	while (current_time - start_time < milisecond)
	{
		if (exit_state(rule))
			break ;
		current_time = get_time_ms(rule);
		usleep(100);
	}
	// TODO: FIX THE SLEEP WHILE;
}
// void	ft_sleep(int milliseconds, t_rules *rule)
// {
// 	int	start_time;
// 	int	target_time;
// 	int	time_left;
// 	start_time = get_time_ms(rule);
// 	target_time = start_time + milliseconds;
// 	time_left = milliseconds;
// 	while (time_left > 0)
// 	{
// 		if (time_left > 10)
// 			usleep(time_left * 800);
// 		else
// 			usleep(100);
// 		time_left = target_time - get_time_ms(rule);
// 	}
// }
