/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:59 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/09 14:26:46 by jwardeng         ###   ########.fr       */
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
	int				tt_sleep;
	int				tt_eat;
	int				tt_die;
	int				own_fork;
	int				righty_fork;
	int				eaten;
	int				philo_nbr;
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
	pthread_mutex_t death_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t	clean_lock;
	int 			ready;
	int				clean;
	int				pl;
	int				philo_nbr;
	int				schnacks;
	int				full;
	struct timeval	starttime;
}					t_data;

typedef struct s_thread_data
{
	t_philo			*philo;
	t_data			*data;
}					t_thread_data;

//      helper
int					ft_atoi(const char *str);
long				current_time(t_philo *philo);
void				print_string(const char *str, t_philo *philo, t_data *data);
void				gettime(t_data **data);
int					ft_usleep(t_philo *philo, t_data *data, long sleep);
//      philo behaviour (philosophy + philo_food)
void				*philo_fun(void *arg);
int					schnacki(t_philo *philo, t_data *data);
int	forever_schleepi(t_philo *philo, t_data *data);
void	return_forks (t_data *data, t_philo *philo, t_philo *righty);
#endif