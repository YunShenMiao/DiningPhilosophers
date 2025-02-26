/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:59 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/26 13:48:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	struct s_philo	*right;
	int				fork;
	int				eaten;
	int				philo_nbr;
	int				tt_sleep;
	int				tt_eat;
	int				tt_die;
	int				schnacks;
	int				id;
	int				philo_died;
	struct timeval	starttime;
	long			lastmeal;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		monitor;
	pthread_mutex_t	print_lock;
	int				philo_nbr;
	int				gesnacked;
	struct timeval	starttime;
}					t_data;

typedef struct s_thread_data
{
	t_philo			*philo;
	t_data			*data;
}					t_thread_data;

//      helper
int					ft_atoi(const char *str);
void				free_threads(t_data **data);
long				current_time(t_philo *philo);
void				print_string(char *str, t_philo *philo, t_data *data);
//      philo behaviour (philosophy + philo_food)
void				*philo_fun(void *arg);
int					schnacki(t_philo *philo, t_data *data);

#endif