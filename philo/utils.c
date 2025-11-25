/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:10:03 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/25 18:18:38 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	asciitouint(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			return (printf("(%s)Only positive numbers are allowed\n", str), -1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (res > INT_MAX)
			return (printf("(%s)Limit is int max\n", str), -1);
	}
	if (str[i] != '\0')
	{
		return (printf("(%s)Only positive numbers are allowed\n", str), -1);
	}
	return ((int)res);
}

bool	one_philo(t_data *data)
{
	if (data->nb_of_philo == 1)
	{
		safe_print(&data->philo[0], data, "has taken a fork");
		usleep(data->ttdie * 1000);
		return (true);
	}
	return (false);
}

void	safe_print(t_philo *philo, t_data *data, char *message)
{
	if (!check_if_dead(data))
		return ;
	pthread_mutex_lock(&data->safe_print);
	printf("%lu %d %s\n", get_time() - data->start_time, philo->id, message);
	pthread_mutex_unlock(&data->safe_print);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	wait_full(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->safe_full);
		if (data->all_full == data->nb_of_philo)
		{
			pthread_mutex_unlock(&data->safe_full);
			break ;
		}
		pthread_mutex_unlock(&data->safe_full);
		if (!check_if_dead(data))
			break ;
		usleep(500);
	}
}
