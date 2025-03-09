/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:48 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/09 14:29:11 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int equality(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (philo->lastmeal > data->philo[i].lastmeal)
		{
		pthread_mutex_unlock(&data->meal_lock);
		return(-1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return(1);
}

int	take_forks(t_philo *philo, t_philo *righty, t_data *data)
{
	while (equality(philo, data) == -1/*  || philo->eaten > righty->eaten */)
	{
		if (forever_schleepi(philo, data) == -1)
		return(-1);
		usleep(100);
	}
/* 	while (philo->eaten > righty->eaten)
	{
		if (forever_schleepi(philo, data) == -1)
		return(-1);
		usleep(100);
	} */
	if (philo->id % 2 == 1/* &philo->lock < &righty->lock */)
	{
		pthread_mutex_lock(&philo->lock);
		philo->own_fork = 1;
		print_string("has taken a fork", philo, data);
		pthread_mutex_lock(&righty->lock);
		print_string("has taken a fork", philo, data);
		philo->righty_fork = 1;
	}
	else
	{
		pthread_mutex_lock(&righty->lock);
		philo->righty_fork = 1;
		print_string("has taken a fork", philo, data);
		pthread_mutex_lock(&philo->lock);
		philo->own_fork = 1;
		print_string("has taken a fork", philo, data);
	}
	return (1);
}

void	return_forks(t_data *data, t_philo *philo, t_philo *righty)
{
/* 	pthread_mutex_lock(&data->clean_lock);
	if (data->clean == 1)
	{
		printf("clean locked\n");
		pthread_mutex_unlock(&data->clean_lock);
	return;
	}
	pthread_mutex_unlock(&data->clean_lock); */
	data->clean = 0;
	if (philo->id % 2 == 1/* &philo->lock < &righty->lock */)
	{
		if (philo->righty_fork == 1)
		{
		pthread_mutex_unlock(&righty->lock);
		philo->righty_fork = 0;
		}
		if (philo->own_fork == 1)
		{
		pthread_mutex_unlock(&philo->lock);
		philo->own_fork = 0;
		}
	}
	else
	{
		if (philo->own_fork == 1)
		{
		pthread_mutex_unlock(&philo->lock);
		philo->own_fork = 0;
		}
		if (philo->righty_fork == 1)
		{
		pthread_mutex_unlock(&righty->lock);
		philo->righty_fork = 0;
		}
	}
}

int	schnacki(t_philo *philo, t_data *data)
{
	t_philo	*righty;

	if (philo->id == data->philo_nbr)
		righty = &data->philo[0];
	else
		righty = &data->philo[philo->id];
	if (take_forks(philo, righty, data) == -1)
		return (-1);
	pthread_mutex_lock(&data->meal_lock);
	philo->lastmeal = current_time(philo);
	pthread_mutex_unlock(&data->meal_lock);
	print_string("is eating", philo, data);
	philo->schnacks--;
	if (ft_usleep(philo, data, philo->tt_eat) == -1)
	return(return_forks(data,philo, righty), -1);
	return_forks(data, philo, righty);
	philo->eaten++;
	return (0);
}
