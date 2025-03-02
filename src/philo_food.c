/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:48 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/02 13:02:28 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int equality(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (philo->lastmeal > data->philo[i].lastmeal)
		return(-1);
		i++;
	}
	return(1);
}

int	take_forks(t_philo *philo, t_philo *righty, t_data *data)
{
	while (equality(philo, data) == -1)
	{
		if (forever_schleepi(philo, data) == -1)
		return(-1);
		usleep(100);
	}
	while (philo->eaten > righty->eaten)
	{
		if (forever_schleepi(philo, data) == -1)
		return(-1);
		usleep(100);
	}
/* 	while (philo->fork == 1 || righty->fork == 1)
	{
		if (philo->philo_died == 1)
		return (-1);
	} */
/* 	if (forever_schleepi(philo, data) == -1)
	return(-1); */
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->lock);
		philo->fork = 1;
		print_string("has taken a fork", philo, data);
		pthread_mutex_lock(&righty->lock);
		print_string("has taken a fork", philo, data);
		righty->fork = 1;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&righty->lock);
		righty->fork = 1;
		print_string("has taken a fork", philo, data);
		pthread_mutex_lock(&philo->lock);
		philo->fork = 1;
		print_string("has taken a fork", philo, data);
	}
	return (1);
}

void	return_forks(t_philo *philo, t_philo *righty)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&righty->lock);
		righty->fork = 0;
		pthread_mutex_unlock(&philo->lock);
		philo->fork = 0;
	}
	else
	{
		pthread_mutex_unlock(&philo->lock);
		philo->fork = 0;
		pthread_mutex_unlock(&righty->lock);
		righty->fork = 0;
	}
}

int	schnacki(t_philo *philo, t_data *data)
{
	int		schnacktime;
	t_philo	*righty;

	schnacktime = philo->tt_eat * 1000;
	if (philo->id == data->philo_nbr)
		righty = &data->philo[0];
	else
		righty = &data->philo[philo->id];
	if (take_forks(philo, righty, data) == -1)
		return (-1);
	if (philo->philo_died == 1)
		return (-1);
	philo->lastmeal = current_time(philo);
	print_string("is eating", philo, data);
	if (ft_usleep(philo, data, philo->tt_eat) == -1)
	return(-1);
	return_forks(philo, righty);
	philo->schnacks--;
	philo->eaten++;
	return (0);
}
