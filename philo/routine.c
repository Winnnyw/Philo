/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:39:16 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/22 22:08:37 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	if (one_philo(data))
	{
		printf("%d\n", data->nb_of_philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (!check_if_dead(data))
			break ;
		if (eating(data, philo))
			break ;
		if (!check_if_dead(data))
			break ;
		sleeper(data, philo);
		if (!check_if_dead(data))
			break ;
		think(data, philo);
		if (!check_if_dead(data))
			break ;
		usleep(900);
	}
	return (NULL);
}

bool	check_if_dead(t_data *data)
{
	pthread_mutex_lock(&data->safe_dead);
	if (data->dead)
		return (pthread_mutex_unlock(&data->safe_dead), false);
	pthread_mutex_unlock(&data->safe_dead);
	return (true);
}

bool	eating(t_data *data, t_philo *philo)
{
	// if (check_if_dead(data))
	{
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, data, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, data, "has taken a fork");
		safe_print(philo, data, "is eating");
		pthread_mutex_lock(&philo->safe_lst_ml);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->safe_lst_ml);
		time_check(data, data->tteat);
		pthread_mutex_lock(&philo->safe_meals);
		philo->nb_of_meals++;
		if (data->max_meals > 0 && philo->nb_of_meals == data->max_meals)
		{
			philo->full = true;
			pthread_mutex_lock(&data->safe_full);
			data->all_full++;
			pthread_mutex_unlock(&data->safe_full);
			pthread_mutex_unlock(&philo->safe_meals);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			wait_full(data);
			return (true);
		}
		pthread_mutex_unlock(&philo->safe_meals);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	return (false);
}

void	sleeper(t_data *data, t_philo *philo)
{
	// if (check_if_dead(data))
	{
		safe_print(philo, data, "is sleeping");
		time_check(data, data->ttsleep);
	}
}

/* void	think(t_data *data, t_philo *philo)
{
	data->ttthink = data->ttdie - data->tteat - data->ttsleep;
	if (data->ttthink < 0)
		data->ttthink = 0;
	safe_print(philo, data, "is thinking");
	time_check(data, data->ttthink);
} */


void	think(t_data *data, t_philo *philo)
{
	int	time_to_think;
	// if (check_if_dead(data))
	{
		time_to_think = data->ttdie - data->tteat
			- data->ttsleep;
		if (time_to_think < 0)
			time_to_think = 0;
		safe_print(philo, data, "is thinking");
	}
}

void	time_check(t_data *data, long time_act)
{
	long	start_act;

	start_act = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->safe_dead);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->safe_dead);
			break;
		}
		pthread_mutex_unlock(&data->safe_dead);
		if (get_time() - start_act > time_act)
			break;
		usleep(900);
	}
}