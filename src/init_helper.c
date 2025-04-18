/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper..c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:25:20 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/18 15:25:23 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(t_simulation_data *data, int argc, char **argv)
{
	data->num_of_philos = (int)ft_atoll(argv[1]);
	data->time_to_die = (int)ft_atoll(argv[2]);
	data->time_to_eat = (int)ft_atoll(argv[3]);
	data->time_to_sleep = (int)ft_atoll(argv[4]);
	if (argc == 6)
		data->must_eat_count = (int)ft_atoll(argv[5]);
	else
		data->must_eat_count = -1;
}
