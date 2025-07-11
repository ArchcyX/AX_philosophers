/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermi <alermi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:04:13 by alermi            #+#    #+#             */
/*   Updated: 2025/07/06 02:08:20 by alermi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	start_control;
	pthread_mutex_t	end_control;
	pthread_mutex_t	total_eaten_meal;
}	t_mutex;

typedef struct s_rules
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				succes_round;
	int				total_eaten_meal;
	int				created_philo;
	int				start;
	int				game_start;
	int				end;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	t_mutex			mutex;
}	t_rules;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		id;
	int				eaten_meal;
	long long		kill_time;
	pthread_mutex_t	kill_control;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	eat_mutex;
	t_rules			*rules;
}	t_philo;

//#############[ INIT & PARSE ]#############//
void	number_check(char *number);
int		ax_atoi(char *number);
int		init_values(int argc, char **argv, t_rules *rules);
int		creat_enviroment(t_rules *head);
int		creat_philo(t_rules *head, int i);
void	fork_init(t_rules *rule);
void	*simulation_init(void *member);

//#############[ STATES ]#############//
void	acting(t_philo *philo);
void	thinking(t_philo *philo);
void	singler_philo(t_philo *philo);
void	*state_controller(t_philo *philo);

//#############[ UTILS ]#############//
void	p_info(t_philo	*philo, char *message);
int		get_time(void);
int		get_time_ms(void *main_struct);
void	ft_sleep(int milisecond, t_rules *rule);

//#############[ ERROR / FREE ]#############//
int		put_error(char *error_message);
void	free_imp(void **allocate);
void	free_matris(void **matris);
void	end_simulation(t_rules *rule);

#endif
