/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:25:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/11 11:39:43 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// meal mutex aendern!!! ueberlegen mit checks und so

#include "philo.h"

int	check_death(t_data *data, int i)
{
	int	mealtime;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->meal_lock);
		mealtime = data->philo[i].lastmeal;
		pthread_mutex_unlock(&data->meal_lock);
		if (mealtime
			+ (long)data->philo[i].tt_die <= current_time(&data->philo[i]))
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_lock);
			printf("%ld %d died\n", current_time(&data->philo[i]),
				data->philo[i].id);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	check_meals(t_data *data, int i)
{
	int	check;

	check = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->snack_lock);
		if (data->philo[i].schnacks > 0 || data->philo[i].schnacks < -9)
			check = 1;
		pthread_mutex_unlock(&data->snack_lock);
		i++;
	}
	pthread_mutex_lock(&data->full_lock);
	if (i == data->philo_nbr && check == 0)
	{
		data->full = -1;
		pthread_mutex_unlock(&data->full_lock);
		return (-1);
	}
	pthread_mutex_unlock(&data->full_lock);
	return (1);
}

void	*monitor_fun(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->philo_nbr == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		if (check_death(data, i) == -1)
			return (NULL);
		if (check_meals(data, i) == -1)
			return (NULL);
	}
	return (NULL);
}
