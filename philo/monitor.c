/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:04:51 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/23 17:05:36 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_monitor_pt2(t_data *data, int i)
{
	if (get_time() - data->philo[i].last_meal >= data->ttdie)
	{
		pthread_mutex_lock(&data->safe_dead);
		data->dead = 1;
		pthread_mutex_unlock(&data->safe_dead);
		pthread_mutex_lock(&data->safe_print);
		printf("%li %d died\n", get_time() - data->start_time, \
			data->philo[i].id);
		pthread_mutex_unlock(&data->safe_print);
		pthread_mutex_unlock(&data->philo[i].safe_lst_ml);
		return (0);
	}
	if (data->max_meals > 0)
	{
		pthread_mutex_lock(&data->safe_full);
		if (data->all_full == data->nb_of_philo)
		{
			pthread_mutex_unlock(&data->safe_full);
			pthread_mutex_unlock(&data->philo[i].safe_lst_ml);
			return (0);
		}
		pthread_mutex_unlock(&data->safe_full);
	}
	return (1);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		if (!check_if_dead(data))
			return (NULL);
		while (i < data->nb_of_philo)
		{
			pthread_mutex_lock(&data->philo[i].safe_lst_ml);
			if (routine_monitor_pt2(data, i) == 0)
				return (NULL);
			pthread_mutex_unlock(&data->philo[i].safe_lst_ml);
			i++;
		}
		usleep(100);
	}
}
