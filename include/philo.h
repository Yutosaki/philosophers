/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:07:52 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/18 16:39:38 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_simulation_data
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					completed_philos;
	bool				is_ate_enough;
	bool				someone_died;
	long long			start_time;
	struct s_philo		*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
}						t_simulation_data;

typedef struct s_philo
{
	int					id;
	int					meals_count;
	long long			last_meal_time;
	bool				has_completed_meals;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_simulation_data	*data;
}						t_philo;

int						init_simulation_data(t_simulation_data *data, int argc,
							char **argv);
int						init_mutexes(t_simulation_data *data);
int						init_philosophers(t_simulation_data *data,
							t_philo **philos);
int						init_fork_mutexes(t_simulation_data *data);
int						init_other_mutexes(t_simulation_data *data);

void					parse_args(t_simulation_data *data, int argc,
							char **argv);
long long				ft_atoll(const char *str);
bool					is_valid_number(const char *str);

void					*select_case(t_philo *philo);
int						start_simulation(t_simulation_data *data,
							t_philo *philos);
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);
bool					is_dead(t_philo *philo);
bool					is_ate_enough(t_simulation_data *data, t_philo *philos);

void					hunger_time_check(t_philo *philo);
void					check_hunger_status(t_philo *philo,
							bool *is_most_hungry, long long my_hunger_time);
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_and_think(t_philo *philo);

long long				get_time(void);
void					print_status(t_philo *philo, char *status);
void					precise_sleep(long long ms);
void					cleanup(t_simulation_data *data, t_philo *philos);
int						ft_strcmp(const char *str1, const char *str2);

#endif // PHILO_H
