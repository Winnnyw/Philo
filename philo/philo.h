/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokilic <rokilic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:35:09 by rokilic           #+#    #+#             */
/*   Updated: 2025/11/23 17:08:49 by rokilic          ###   ########.fr       */
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
# include <sys/wait.h>
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
	pthread_mutex_t	safe_lst_ml;
	long			last_meal;
	int				nb_of_meals;
	bool			full;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				ttthink;
	int				nb_of_philo;
	int				all_full;
	long			start_time;
	struct s_philo	philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	safe_dead;
	pthread_mutex_t	safe_full;
	pthread_mutex_t	safe_print;
	pthread_mutex_t	safe_start;
	int				start;
	int				dead;
	int				max_meals;

}					t_data;

// utils
int				asciitouint(char *str);
bool			one_philo(t_data *data);
long			get_time(void);
void			safe_print(t_philo *philo, t_data *data, char *message);
bool			check_if_dead(t_data *data);
void			time_check(t_data *data, long time_act);
void			destroy_mutexes(t_data *data);

// routine
void			*routine(void *arg);
bool			eating(t_data *data, t_philo *philo);
void			sleeper(t_data *data, t_philo *philo);
void			think(t_data *data, t_philo *philo);
void			wait_full(t_data *data);
int				routine_pt_1(t_philo *philo, t_data *data);

// monitor
void			*routine_monitor(void *arg);

#endif
