/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:39:16 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/08 17:15:31 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int	i;
	i = 0;

	philo = (t_philo *)arg;
	data = philo->data;
	if (one_philo(data))
		return (NULL);
	while (i < data->max_meals)
	{
		
	}
	return (NULL);
}

void 