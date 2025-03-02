/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/02 12:58:54 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinky(t_philo *philo, t_data *data)
{
	if (forever_schleepi(philo, data) == -1)
	return(-1);
	if (philo->philo_died == 1)
		return (-1);
	print_string("is thinking", philo, data);
	return (0);
}

int	schleepi(t_philo *philo, t_data *data)
{
	if (philo->philo_died == 1)
		return (-1);
	print_string("is sleeping", philo, data);
	if (ft_usleep(philo, data, philo->tt_sleep) == -1)
	return(-1);
	return (1);
}

int	forever_schleepi(t_philo *philo, t_data *data)
{
	/* printf("id: %d, lm: %ld ttd %d ct %ld\n", philo->id, philo->lastmeal, philo->tt_die, current_time(philo)); */
	if (philo->lastmeal + (long)philo->tt_die <= current_time(philo))
	{
		pthread_mutex_lock(&data->death_lock);
		if (philo->philo_died == 1)
		return (pthread_mutex_unlock(&data->death_lock), -1);
		print_string("died", philo, data);
		philo->philo_died = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (-1);
	}
	return (1);
}

void	*philo_fun(void *arg)
{
	t_thread_data	*threaddata;
	t_data			*data;
	t_philo			*philo;

	threaddata = (t_thread_data *)arg;
	data = threaddata->data;
	philo = threaddata->philo;
	free(threaddata);
	if (philo->id % 2 == 0)
	ft_usleep(philo, data, 1);
	while (philo->philo_died == 0)
	{
		if (forever_schleepi(philo, data) == -1)
			break ;
		if (schnacki(philo, data) == -1)
			break ;
		if (forever_schleepi(philo, data) == -1)
			break ;
		if (schleepi(philo, data) == -1)
			break ;
					if (forever_schleepi(philo, data) == -1)
			break ;
		if (thinky(philo, data) == -1)
			break ;
	}
	return (NULL);
}

// eat -> sleep -> think