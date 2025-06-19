/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:12:32 by alermi            #+#    #+#             */
/*   Updated: 2025/06/17 20:29:42 by alermi           ###   ########.fr       */
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
 		current_time = get_time_ms(rule);
 		usleep(100);
 	}
}
//void	ft_sleep(int milliseconds, t_rules *rule)
//{
//	int	start_time;
//	int	target_time;
//	int	time_left;
//
//	start_time = get_time_ms(rule);
//	target_time = start_time + milliseconds;
//	time_left = milliseconds;
//	while (time_left > 0)
//	{
//		if (time_left > 10)
//			usleep(time_left * 800); // uyuma süresi hedefin biraz altında kalsın
//		else
//			usleep(100); // çok kısa kalan sürelerde hassas uyuma
//		time_left = target_time - get_time_ms(rule);
//	}
//}
