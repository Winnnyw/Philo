/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:35:30 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/08 17:09:25 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_of_philo = asciitouint(av[1]);
	data->ttdie = asciitouint(av[2]);
	data->tteat = asciitouint(av[3]);
	data->ttsleep = asciitouint(av[4]);
	if (ac == 6)
		data->max_meals = asciitouint(av[5]);
	else
		data->max_meals = INT_MAX;
	if (data->nb_of_philo < 0 || data->ttdie < 0 || data->tteat < 0 || data->ttsleep < 0)
		return(-1);
	return (0);
}

void	init_philos(t_data *data)
{
	int i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].nb_of_meals = 0;
		pthread_mutex_init(&data->philo[i].safe_meals, NULL);
		data->philo[i].l_fork = &data->fork[i];
		if (i + 1 == data->nb_of_philo)
			data->philo[i].r_fork = &data->fork[0];
		else
			data->philo[i].r_fork = &data->fork[i + 1];
		pthread_create(&data->philo[i].philo_thread, NULL, routine, &data->philo[i]);
		i++;
	}
}
int	main(int ac, char **av)
{
	t_data	data;
	int i;

	data = (t_data){0};
	if (!(ac >= 5 && ac <= 6))
		return (printf(ERR), 0);
	if (init_data(&data, ac, av) != 0)
		return (0);
	init_philos(&data);
	i = 0;
	while (i < data.nb_of_philo)
	{
		pthread_join(data.philo[i].philo_thread, NULL);
		i++;
	}
	printf("philos %d\ndie %d\neat %d\nsleep %d\nmax meals %d\n", data.nb_of_philo, data.ttdie, data.tteat, data.ttsleep, data.max_meals);
}
/*
	- ./philo 1 200 200 200 -> print
	- structut -> liste chainee ? tableau ? ->
	-fsanitize=mutex
	valgrind -tools=helgrind  ./philo
*/