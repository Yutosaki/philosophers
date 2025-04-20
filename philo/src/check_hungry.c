/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hungry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:26:53 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/18 15:26:54 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_hunger_status(t_philo *philo, bool *is_most_hungry,
		long long my_hunger_time)
{
	int			i;
	long long	other_hunger_time;
	long long	current_time;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		if (philo->data->philos[i].id != philo->id)
		{
			current_time = get_time();
			pthread_mutex_lock(&philo->data->meal_mutex);
			other_hunger_time = current_time
				- philo->data->philos[i].last_meal_time;
			pthread_mutex_unlock(&philo->data->meal_mutex);
			if (other_hunger_time > my_hunger_time)
			{
				*is_most_hungry = false;
				break ;
			}
		}
		i++;
	}
}

void	hunger_time_check(t_philo *philo)
{
	long long	my_hunger_time;
	bool		is_most_hungry;

	while (1)
	{
		is_most_hungry = true;
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died || philo->data->is_ate_enough)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->meal_mutex);
		my_hunger_time = get_time() - philo->last_meal_time;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		check_hunger_status(philo, &is_most_hungry, my_hunger_time);
		if (is_most_hungry)
			break ;
		precise_sleep(philo->data->time_to_eat / philo->data->num_of_philos);
	}
}
