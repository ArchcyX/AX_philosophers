/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:00:22 by alermi            #+#    #+#             */
/*   Updated: 2025/04/27 18:19:50 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

enum e_state
{
	e_thinking,
	e_sleeping,
	e_eating
};

typedef struct s_philo t_philo;

typedef struct  s_rules
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				succes_round;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
	int				created_philo;
	int				start;
	int				game_start;
	int				end;
}   t_rules;

typedef struct s_philo
{
	int				philo_id;
	pthread_t       id;
	int             eat_meal;
	long long       last_meal;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_rules			*rules;
}   t_philo;

void	number_check(char *number);
int		ax_atoi(char *number);

//#############[State Funtions]#############//

void	*state_selector(t_philo *philo);
void	p_eat(t_philo *philo);
void	p_sleep(t_philo *philo);


//#############[INIT Funtions]#############//

void	init_values(int argc, char **argv, t_rules *rule);
int		creat_enviroment(t_rules *head);
int		creat_philo(t_rules *head, int i);
void	*simulation_init(void *member);

//#############[Fork Funtions]#############//

int	fork_init(t_rules *rule);

//#############[Error functions]#############//

int		put_error(char *error_message);
void	free_imp(void *allocate);
void	free_matris(void **matris);

//#############[Time-functions]#############//

int		get_time(void *main_struct);
int		get_time_ms(void *main_struct);
void	ft_sleep(int milisecond, t_rules *rule);
void	p_info(t_philo	*philo, char *message);

#endif