/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:48 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/26 13:38:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, t_philo *righty, t_data *data)
{
	if (philo->philo_died == 1)
		return (-1);
	while (philo->eaten > righty->eaten)
		usleep(10);
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
	righty = philo->right;
	if (take_forks(philo, righty, data) == -1)
		return (-1);
	print_string("is eating", philo, data);
	usleep(schnacktime);
	philo->lastmeal = current_time(philo);
	return_forks(philo, righty);
	philo->schnacks--;
	philo->eaten++;
	return (0);
}
