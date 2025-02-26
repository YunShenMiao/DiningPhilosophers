/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/26 13:46:15 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinky(t_philo *philo, t_data *data)
{
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
	usleep(philo->tt_sleep * 1000);
	return (1);
}

int	forever_schleepi(t_philo *philo, t_data *data)
{
	if (philo->lastmeal + (long)philo->tt_die < current_time(philo))
	{
		philo->philo_died = 1;
		print_string("died", philo, data);
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
	while (philo->philo_died == 0)
	{
		if (forever_schleepi(philo, data) == -1)
			break ;
		if (thinky(philo, data) == -1)
			break ;
		if (forever_schleepi(philo, data) == -1)
			break ;
		if (schnacki(philo, data) == -1)
			break ;
		if (forever_schleepi(philo, data) == -1)
			break ;
		if (schleepi(philo, data) == -1)
			break ;
	}
	return (NULL);
}

// eat -> sleep -> think