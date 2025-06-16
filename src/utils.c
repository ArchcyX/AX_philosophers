/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:17 by alermi            #+#    #+#             */
/*   Updated: 2025/06/16 18:29:05 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

extern __inline__ void
	number_check(char *number)
{
	int	i;

	i = 0;
	if (number[i] == '+' || number[i] == '-')
		i++;
	i--;
	while (number[++i])
//		if (number[i] < '0' || number[i] > '9' || i > 11)
//			error_exit("Error!!", 1);
		return ;
}

int	ax_atoi(char *number)
{
	int		sign;
	size_t	res;
	size_t	i;

	i = 0;
	sign = 1;
	res = 0;
	number_check(number);
	while (number[i] <= 32 && number[i] != 0)
		i++;
	if (number[i] == '+' || number[i] == '-')
	{
		if (number[i] == '-')
			sign = -1;
		i++;
	}
	while (number[i] >= '0' && number[i] <= '9')
	{
		res = (res * 10) + (number[i] - '0');
		i++;
	}
//	if (res > 2147483647 - (sign - 1) / 2)
//		error_exit("Error!!", 1);
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
