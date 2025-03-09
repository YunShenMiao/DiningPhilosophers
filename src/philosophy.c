/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/09 14:26:48 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinky(t_philo *philo, t_data *data)
{
	if (forever_schleepi(philo, data) == -1)
	return(-1);
	/* if (philo->philo_died == 1 || data->full == -1)
		return (-1); */
		pthread_mutex_lock(&data->death_lock);
	if (philo->philo_died == 1)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (-1);
	}
	pthread_mutex_unlock(&data->death_lock);
	print_string("is thinking", philo, data);
	return (0);
}

int	schleepi(t_philo *philo, t_data *data)
{
	/* if (philo->philo_died == 1 || data->full == -1)
		return (-1); */
	if (forever_schleepi(philo, data) == -1)
	return(-1);
	pthread_mutex_lock(&data->death_lock);
	if (philo->philo_died == 1)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (-1);
	}
	pthread_mutex_unlock(&data->death_lock);
	print_string("is sleeping", philo, data);
	if (ft_usleep(philo, data, philo->tt_sleep) == -1)
	return(-1);
	return (1);
}

// maybe issue deadlock, issue when philo dies after trying to fix some hellgrind stufff...
int	forever_schleepi(t_philo *philo, t_data *data)
{
	/* printf("id: %d, lm: %ld ttd %d ct %ld\n", philo->id, philo->lastmeal, philo->tt_die, current_time(philo)); */
	pthread_mutex_lock(&data->meal_lock);
	if (data->full == -1)
	return(pthread_mutex_unlock(&data->meal_lock), -1);
	pthread_mutex_unlock(&data->meal_lock);
	if (philo->lastmeal + (long)philo->tt_die <= current_time(philo))
	{
		pthread_mutex_lock(&data->death_lock);
		if (philo->philo_died == 1)
		{
			pthread_mutex_unlock(&data->death_lock);
			return (-1);
		}
		print_string("died", philo, data);
		philo->philo_died = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (-1);
	}
	return (1);
}

void one_philo(t_philo *philo, t_data *data)
{
	ft_usleep(philo, data, philo->tt_die);
	print_string("died", philo, data);
}

void	*philo_fun(void *arg)
{
	t_thread_data	*threaddata;
	t_data			*data;
	t_philo			*philo;
	int x;

	threaddata = (t_thread_data *)arg;
	data = threaddata->data;
	philo = threaddata->philo;
	while(1)
	{
		pthread_mutex_lock(&data->print_lock);
		x = data->ready;
		pthread_mutex_unlock(&data->print_lock);
		if (x == 1)
		break;
		usleep(100);
	}
	if (philo->id % 2 == 0)
	ft_usleep(philo, data, 1);
	if (data->philo_nbr == 1)
	{
		one_philo(philo, data);
		return(NULL);
	}
	while (1)
	{
		if (schnacki(philo, data) == -1)
			break ;
		if (schleepi(philo, data) == -1)
			break ;
		if (thinky(philo, data) == -1)
			break ;
	}
	free(threaddata);
	usleep(10000);
	return (NULL);
}

// eat -> sleep -> think