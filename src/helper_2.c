/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:28:01 by yutsasak          #+#    #+#             */
/*   Updated: 2025/04/18 15:30:15 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_number(const char *str)
{
	int			i;
	long long	max_check;

	i = 0;
	if (str[i] == '-')
		return (false);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	max_check = ft_atoll(str);
	if (max_check > INT_MAX || max_check < INT_MIN)
		return (false);
	return (true);
}
