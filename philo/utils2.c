/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:52:44 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/23 17:57:59 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_pt_1(t_philo *philo, t_data *data)
{
	if (data->nb_of_philo == 1 && one_philo(data))
		return (0);
	pthread_mutex_lock(&data->safe_start);
	while (data->start != 1)
	{
		pthread_mutex_unlock(&data->safe_start);
		usleep(100);
		pthread_mutex_lock(&data->safe_start);
	}
	pthread_mutex_unlock(&data->safe_start);
	if (philo->id % 2 == 0)
		usleep(1000);
	return (1);
}

bool	check_if_dead(t_data *data)
{
	pthread_mutex_lock(&data->safe_dead);
	if (data->dead)
		return (pthread_mutex_unlock(&data->safe_dead), false);
	pthread_mutex_unlock(&data->safe_dead);
	return (true);
}
