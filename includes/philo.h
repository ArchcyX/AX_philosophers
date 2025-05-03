/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:00:22 by alermi            #+#    #+#             */
/*   Updated: 2025/05/03 16:48:53 by alermi           ###   ########.fr       */
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

typedef struct	s_mutex
{
	pthread_mutex_t	start_control;
	pthread_mutex_t	end_control;
	pthread_mutex_t	total_eaten_meal;
}	t_mutex;

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
	int				total_eaten_meal;
	int				created_philo;
	int				start;
	int				game_start;
	int				end;
	t_mutex			mutex;
}   t_rules;

typedef struct s_philo
{
	int				philo_id;
	pthread_t       id;
	int             eat_meal;
	int				eaten_meal;
	long long		kill_time;
	pthread_mutex_t	kill_control;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_rules			*rules;
}   t_philo;

void	number_check(char *number);
int		ax_atoi(char *number);

//#############[State Funtions]#############//

void	*state_selector(t_philo *philo);
void	acting(t_philo *philo);
void	end_simulation(t_rules	*rule);


//#############[INIT Funtions]#############//

int		creat_enviroment(t_rules *head);
int		creat_philo(t_rules *head, int i);
void	*simulation_init(void *member);

//#############[Fork Funtions]#############//

void	fork_init(t_rules *rule);

//#############[Error functions]#############//

int		put_error(char *error_message);
void	free_imp(void **allocate);
void	free_matris(void **matris);

//#############[Time-functions]#############//

int		get_time(void);
int		get_time_ms(void *main_struct);
void	ft_sleep(int milisecond, t_rules *rule);
void	p_info(t_philo	*philo, char *message);

#endif