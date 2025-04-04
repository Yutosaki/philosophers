/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:07:52 by yutsasak          #+#    #+#             */
/*   Updated: 2025/03/19 21:29:52 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define FORK_TAKEN "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

typedef struct s_simulation_data {
  int num_of_philos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int num_times_to_eat;
  bool is_ate_enough;
  bool someone_died;
  long long start_time;
  pthread_mutex_t *forks;
  pthread_mutex_t print_mutex;
  pthread_mutex_t death_mutex;
  pthread_mutex_t meal_mutex;
} t_simulation_data;

typedef struct s_philo {
  int id;
  int meals_count;
  long long last_meal_time;
  pthread_t thread;
  pthread_mutex_t *left_fork;
  pthread_mutex_t *right_fork;
  t_simulation_data *data;
} t_philo;

/* Initialization */
int init_simulation_data(t_simulation_data *data, int argc, char **argv);
int init_mutexes(t_simulation_data *data);
int init_philosophers(t_simulation_data *data, t_philo **philos);

/* Parsing */
void parse_args(t_simulation_data *data, int argc, char **argv);
int ft_atoi(const char *str);
bool is_valid_number(const char *str);

/* Simulation */
int start_simulation(t_simulation_data *data, t_philo *philos);
void *philosopher_routine(void *arg);
void *monitor_routine(void *arg);
bool is_dead(t_philo *philo);
bool is_ate_enough(t_simulation_data *data, t_philo *philos);

/* Actions */
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void sleep_and_think(t_philo *philo);

/* Utilities */
long long get_time(void);
void print_status(t_philo *philo, char *status);
void precise_sleep(long long ms);
void cleanup(t_simulation_data *data, t_philo *philos);

#endif
