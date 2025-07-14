/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:17 by alermi            #+#    #+#             */
/*   Updated: 2025/07/14 02:24:47 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

int	number_check(char *number)
{
	int	i;

	if (!number || !*number)
		return (put_error("Error: Empty input!"));
	i = 0;
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (put_error("Error: Invalid format!"));
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
			return(put_error("Error: Invalid character in number!"));
		i++;
	}
	return (0);
}

int	ax_atoi(char *number)
{
	int		sign;
	long	res;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	if(number_check(number))
		return (-1);
	while ((number[i] >= 9 && number[i] <= 13) || number[i] == 32)
		i++;
	if (number[i] == '+' || number[i] == '-')
	{
		if (number[i] == '-')
			sign = -1;
		i++;
	}
	while (number[i] >= '0' && number[i] <= '9')
	{
		res = res * 10 + (number[i] - '0');
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && -res < INT_MIN))
			return (put_error("Error: Integer overflow!") - 2);
		i++;
	}
	return ((int)(res * sign));
}

void	p_info(t_philo	*philo, char *message)
{
	int	current_time;

	pthread_mutex_lock(&philo->rules->mutex.end_control);
	if (!philo->rules->end)
	{
		pthread_mutex_unlock(&philo->rules->mutex.end_control);
		current_time = get_time_ms((void *)philo->rules);
		printf("%d  %d %s\n", current_time, philo->philo_id, message);
	}
	else
		pthread_mutex_unlock(&philo->rules->mutex.end_control);
}
