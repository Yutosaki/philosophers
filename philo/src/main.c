/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:29:12 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/10 20:07:48 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (true);
	}
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4]) || (argc == 6
			&& !is_valid_number(argv[5])))
	{
		printf("Error: Arguments must be positive integers\n");
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	t_simulation_data	data;
	t_philo				*philos;

	if (is_error(argc, argv))
		return (1);
	if (init_simulation_data(&data, argc, argv))
		return (1);
	if (init_philosophers(&data, &philos))
	{
		cleanup(&data, NULL);
		return (1);
	}
	if (start_simulation(&data, philos))
	{
		cleanup(&data, philos);
		return (1);
	}
	cleanup(&data, philos);
	return (0);
}
