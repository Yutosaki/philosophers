/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:24:00 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/08 22:52:29 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo				*philos;
	t_simulation_data	*data;
	int					i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (is_dead(&philos[i]))
				return (NULL);
			i++;
		}
		if (is_ate_enough(data, philos))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void *case_one_philo(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_TAKEN);
	precise_sleep(philo->data->time_to_die);
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", current_time, philo->id, DIED);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->data->num_of_philos == 1)
	    return(case_one_philo(philo));
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2); // 待ち時間がちょうど良くなる?
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died || philo->data->is_ate_enough)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_simulation_data *data, t_philo *philos)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	i = 0;
	while (i < data->num_of_philos)
		pthread_join(philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
