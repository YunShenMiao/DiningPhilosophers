/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:48 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/24 14:25:16 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo, t_data *data)
{
	ft_usleep(philo, philo->tt_die);
	print_string("died", philo, data);
}

int	equality(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (philo->lastmeal > data->philo[i].lastmeal)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return (-1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (1);
}

void	take_forks(t_philo *philo, t_philo *righty, t_data *data)
{
	// if (data->philo_nbr % 2 != 0)
	// {
	// 	while (equality(philo, data) == -1)
	// 		ft_usleep(philo, 10);
	// }
	if (philo->id % 2 == 1)
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
}

void	return_forks(t_philo *philo, t_philo *righty)
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

int	schnacki(t_philo *philo, t_data *data)
{
	t_philo	*righty;

	if (philo->id == data->philo_nbr)
		righty = &data->philo[0];
	else
		righty = &data->philo[philo->id];
	take_forks(philo, righty, data);
	pthread_mutex_lock(&data->meal_lock);
	philo->lastmeal = current_time(philo);
	pthread_mutex_unlock(&data->meal_lock);
	pthread_mutex_lock(&data->snack_lock);
	philo->schnacks--;
	pthread_mutex_unlock(&data->snack_lock);
	print_string("is eating", philo, data);
	ft_usleep(philo, philo->tt_eat);
	return_forks(philo, righty);
	return (0);
}
