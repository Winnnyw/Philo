/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:10:03 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/08 17:09:46 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	asciitouint(char *str)
{
	int i = 0;
	long res = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (printf("(%s)Only positive numbers are accepted\n", str), -1);
		i++;
	}
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)res);
}

bool	one_philo(t_data *data)
{
	if (data->nb_of_philo == 1)
	{
		printf("1 has taken a fork\n");
		usleep(data->ttdie * 1000);
		printf("1 died\n");
		return (true);
	}
	return (false);
}