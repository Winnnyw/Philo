/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:35:09 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/08 17:01:08 by rokilic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define ERR "Wrong number of arguments : ./philo [nb_of_philo] \
	[tt_die] [tt_eat] [tt sleep] ?[nb_of_meals]\n"

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	safe_meals;
	int				nb_of_meals;
	struct s_data *data;

}					t_philo;

typedef struct s_data
{
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				ttthink;
	int				nb_of_philo;
	long			start_time;
	struct s_philo	philo[200];
	pthread_mutex_t	fork[200];
	int				dead;
	int				max_meals;

}					t_data;

// utils
int				asciitouint(char *str);
bool			one_philo(t_data *data);

// routine
void			*routine(void *arg);
#endif
