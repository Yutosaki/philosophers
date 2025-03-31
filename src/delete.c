/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:25:00 by yutsasak          #+#    #+#             */
/*   Updated: 2025/03/28 12:29:55 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_simulation_data *data, t_philo *philos)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		free(data->forks);
	}
	if (philos)
		free(philos);
}
