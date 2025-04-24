/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/24 16:42:57 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change: monitor is checking last meal constantly for all philos,
// sets bool finish to 1 immediately
// in philo checks the bool to stop the program
// as soon as 1 & thread prints the message
// mutex to protect philo from die when start eat.

#include "philo.h"

void	thinky(t_philo *philo, t_data *data)
{
	print_string("is thinking", philo, data);
}

void	schleepi(t_philo *philo, t_data *data)
{
	print_string("is sleeping", philo, data);
	ft_usleep(philo, philo->tt_sleep);
}

int	forever_schleepi(t_data *data)
{
	int	x;

	pthread_mutex_lock(&data->full_lock);
	x = data->full;
	pthread_mutex_unlock(&data->full_lock);
	if (x == -1)
		return (-1);
	pthread_mutex_lock(&data->beg_stop_lock);
	x = data->beg_stop;
	pthread_mutex_unlock(&data->beg_stop_lock);
	if (x == -1)
		return (-1);
	return (1);
}

void	wait_threads(t_data *data)
{
	int	begin;

	while (1)
	{
		pthread_mutex_lock(&data->beg_stop_lock);
		begin = data->beg_stop;
		pthread_mutex_unlock(&data->beg_stop_lock);
		if (begin == 1)
			break ;
		usleep(100);
	}
}

void	*philo_fun(void *arg)
{
	t_philo_con	*philocontext;
	t_data			*data;
	t_philo			*philo;

	philocontext = (t_philo_con *)arg;
	data = philocontext->data;
	philo = philocontext->philo;
	free(philocontext);
	wait_threads(data);
	if (data->philo_nbr == 1)
		return (one_philo(philo, data), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo, 20/* philo[0].tt_eat / 2 */);
	while (1)
	{
		if (forever_schleepi(data) == -1)
			break ;
		thinky(philo, data);
		schnacki(philo, data);
		schleepi(philo, data);
	}
	usleep(500);
	return (NULL);
}
