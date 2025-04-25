/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:59 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/25 17:21:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/*									STRUCTS									  */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				tt_sleep;
	int				tt_eat;
	int				tt_die;
	int				own_fork;
	int				righty_fork;
	int				schnacks;
	int				id;
	struct timeval	starttime;
	long			lastmeal;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		monitor;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	snack_lock;
	pthread_mutex_t	beg_stop_lock;
	int				beg_stop;
	int				philo_nbr;
	int				full;
	struct timeval	starttime;
}					t_data;

typedef struct s_philo_con
{
	t_philo			*philo;
	t_data			*data;
}					t_philo_con;

/* ************************************************************************** */
/*                                                                            */
/*									FUNCTIONS								  */
/*                                                                            */
/* ************************************************************************** */

//      helper
int					ft_atoi(const char *str);
long				current_time(t_philo *philo);
void				print_string(const char *str, t_philo *philo, t_data *data);
void				gettime(t_data **data);
int					ft_usleep(t_philo *philo, long sleep);
//      philo behaviour (philosophy + philo_food)
void				*philo_fun(void *arg);
int					schnacki(t_philo *philo, t_data *data);
int					forever_schleepi(t_data *data);
void				one_philo(t_philo *philo, t_data *data);
//		data initialization
int					init_data(int argc, char *argv[], t_data **data);
// 		monitoring
void				*monitor_fun(void *arg);

#endif