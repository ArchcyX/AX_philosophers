/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:11:53 by alermi            #+#    #+#             */
/*   Updated: 2025/04/13 19:58:57 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
//printf()
# include <stdlib.h>
//Malloc() Free()
# include <string.h>
//memset()
# include <unistd.h>
//write()
# include <pthread.h>
//Thread functions()

typedef struct s_rules
{
    int             philo_count;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_must_eat;
    long long       start_time;
    int             someone_die;
    pthread_mutex_t *forks;
	pthread_mutex_t print;
}   t_rules;

typedef struct s_philos
{
    int             id;
    int             meal_eaten;
    long long       last_meals;
    t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}   t_philos;

//#############[Utils Functions]#############//

void	ft_putstr(char *str);

//#############[Error Functions]#############//

void	ax_error(char *error_message);

#endif