/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:19:50 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/08 22:40:48 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, EATING);
	precise_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void    sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_sleep(philo->data->time_to_sleep);
	print_status(philo, THINKING);
}

bool    is_dead(t_philo *philo)
{
	long long	current_time;
	bool		is_dead;

	is_dead = false;
	pthread_mutex_lock(&philo->data->meal_mutex);
	if ((get_time() - philo->last_meal_time) > philo->data->time_to_die)
		is_dead = true;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (is_dead)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (!philo->data->someone_died)
		{
			philo->data->someone_died = true;
            pthread_mutex_lock(&philo->data->print_mutex);
            current_time = get_time() - philo->data->start_time;
            printf("%lld %d %s\n", current_time, philo->id, DIED);
            pthread_mutex_unlock(&philo->data->print_mutex);
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
        return (true);
    }
	return (false);
}

bool	is_ate_enough(t_simulation_data *data, t_philo *philos)
{
	int	i;
	int	count;

	if (data->must_eat_count == -1)
		return (false);
	count = 0;
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (philos[i].meals_count >= data->must_eat_count)
			count++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (count == data->num_of_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->is_ate_enough = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	return (false);
}
