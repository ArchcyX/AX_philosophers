/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:00:22 by alermi            #+#    #+#             */
/*   Updated: 2025/04/23 18:50:18 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t       id;
	int             eat_meal;
	long long       last_meal;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
}   t_philo;

typedef struct  s_rules
{
	int             count_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int				succes_round;
	t_philo         *philos;
	pthread_mutex_t *fork;
	pthread_mutex_t	mutex;
	int				created_philo;
}   t_rules;

void	number_check(char *number);
void	init_values(int argc, char **argv, t_rules *rule);
int		ax_atoi(char *number);
void	*state_selector(void *main_struct);

//#############[Thread Funtions]#############//

int		creat_enviroment(t_rules *head);
int		creat_philo(t_rules *head, int i);

//#############[Fork Funtions]#############//

int	fork_init(t_rules *rule);

//#############[Error functions]#############//

int		put_error(char *error_message);
void	free_imp(void *allocate);
void	free_matris(void **matris);

#endif