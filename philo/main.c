/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:35:30 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/23 16:04:29 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].safe_meals);
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].safe_lst_ml);
		i++;
	}
	pthread_mutex_destroy(&data->safe_full);
	pthread_mutex_destroy(&data->safe_dead);
	pthread_mutex_destroy(&data->safe_print);
	pthread_mutex_destroy(&data->safe_start);

}

int	init_data(t_data *data, int ac, char **av)
{
	data->dead = 0;
	data->all_full = 0;
	data->start = 0;
	data->start_time = get_time();
	data->nb_of_philo = asciitouint(av[1]);
	data->ttdie = asciitouint(av[2]);
	data->tteat = asciitouint(av[3]);
	data->ttsleep = asciitouint(av[4]);
	if (ac == 6)
		data->max_meals = asciitouint(av[5]);
	else
		data->max_meals = -1;
	if (data->nb_of_philo <= 0 || data->ttdie < 0 || data->tteat < 0 || \
		data->ttsleep < 0)
		return (-1);
	pthread_mutex_init(&data->safe_full, NULL);
	pthread_mutex_init(&data->safe_dead, NULL);
	pthread_mutex_init(&data->safe_print, NULL);
	pthread_mutex_init(&data->safe_start, NULL);

	return (0);
}

void	init_philos(t_data *data, pthread_t *monitor)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].nb_of_meals = 0;
		data->philo[i].full = false;
		data->philo[i].last_meal = data->start_time;
		pthread_mutex_init(&data->philo[i].safe_lst_ml, NULL);
		pthread_mutex_init(&data->philo[i].safe_meals, NULL);
		data->philo[i].l_fork = &data->fork[i];
		if (i + 1 == data->nb_of_philo)
		{
			
			data->philo[i].l_fork = &data->fork[0];
			data->philo[i].r_fork = &data->fork[i];
		}
		else
			data->philo[i].r_fork = &data->fork[i + 1];
	
		pthread_create(&data->philo[i].philo_thread, NULL, routine, \
			&data->philo[i]);
		i++;
	}
	pthread_create(monitor, NULL, routine_monitor, \
			data);
}
/*Les threads doivent artir a un go
le feu est mis au rouge au depart
tous le sthreads, une fois lances attendent que le feu passe au vert (dans les fonctions routines)
on passe le feu au vert une fois qu'ils ont ete tous crees
dans les threads, on lit que le feu passe au vert, on avance dans le code..*/
int	main(int ac, char **av)
{
	t_data	data;
	pthread_t monitor;
	int		i;

	data = (t_data){0};
	if (!(ac >= 5 && ac <= 6))
		return (printf(ERR), 0);
	if (init_data(&data, ac, av) != 0)
		return (0);
	init_philos(&data, &monitor);
	pthread_mutex_lock(&data.safe_start);
	data.start = 1;
	pthread_mutex_unlock(&data.safe_start);
	// ici, tous les threads ont ete created, on peut dire que le feu est vert
	i = 0;
	while (i < data.nb_of_philo)
	{
		pthread_join(data.philo[i].philo_thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	destroy_mutexes(&data);
	// printf("philos %d\ndie %d\neat %d\nsleep %d\nmax meals %d\n", data.nb_of_philo, data.ttdie, data.tteat, data.ttsleep, data.max_meals);
}
/*
	- ./philo 1 200 200 200 -> print
	- structut -> liste chainee ? tableau ? ->
	-fsanitize=mutex
	valgrind -tools=helgrind  ./philo
*/