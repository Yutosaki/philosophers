/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:21:00 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/18 15:26:25 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_simulation_data *data)
{
	if (init_fork_mutexes(data) != 0)
		return (1);
	if (init_other_mutexes(data) != 0)
		return (1);
	return (0);
}

int	init_other_mutexes(t_simulation_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		i = 0;
		while (i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
		return (1);
	}
	return (0);
}

int	init_fork_mutexes(t_simulation_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_simulation_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!*philos)
		return (1);
	data->philos = *philos;
	i = 0;
	while (i < data->num_of_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_count = 0;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].data = data;
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->num_of_philos];
		i++;
	}
	return (0);
}

int	init_simulation_data(t_simulation_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_simulation_data));
	parse_args(data, argc, argv);
	data->is_ate_enough = false;
	data->someone_died = false;
	if (init_mutexes(data))
	{
		printf("Error: Failed to initialize mutexes\n");
		return (1);
	}
	return (0);
}
