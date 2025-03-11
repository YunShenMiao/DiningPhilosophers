/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:45:16 by jwardeng          #+#    #+#             */
/*   Updated: 2025/03/11 11:50:24 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data **data, int i)
{
	t_thread_data	*threaddata;

	threaddata = malloc(sizeof(t_thread_data));
	if (threaddata == NULL)
		return (-1);
	(*data)->schnacks = (*data)->philo[0].schnacks;
	threaddata->data = (*data);
	threaddata->philo = &(*data)->philo[i];
	if (pthread_create(&(*data)->philo[i].thread, NULL, &philo_fun,
			threaddata) != 0)
		return (free(threaddata), -1);
	return (1);
}

int	init_philo(int argc, char *argv[], t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nbr)
	{
		pthread_mutex_init(&(*data)->philo[i].lock, NULL);
		(*data)->philo[i].philo_nbr = (*data)->philo_nbr;
		(*data)->philo[i].starttime = (*data)->starttime;
		(*data)->philo[i].lastmeal = 0;
		(*data)->philo[i].id = i + 1;
		(*data)->philo[i].tt_die = ft_atoi(argv[2]);
		(*data)->philo[i].tt_eat = ft_atoi(argv[3]);
		(*data)->philo[i].tt_sleep = ft_atoi(argv[4]);
		(*data)->philo[i].own_fork = 0;
		(*data)->philo[i].righty_fork = 0;
		if (argc == 6)
			(*data)->philo[i].schnacks = ft_atoi(argv[5]);
		else
			(*data)->philo[i].schnacks = -10;
		if (init_threads(data, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_data(int argc, char *argv[], t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	(*data)->philo_nbr = ft_atoi(argv[1]);
	(*data)->full = 0;
	(*data)->ready = 0;
	(*data)->stop = 0;
	(*data)->pl = 0;
	pthread_mutex_init(&(*data)->print_lock, NULL);
	pthread_mutex_init(&(*data)->meal_lock, NULL);
	pthread_mutex_init(&(*data)->full_lock, NULL);
	pthread_mutex_init(&(*data)->snack_lock, NULL);
	pthread_mutex_init(&(*data)->stop_lock, NULL);
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nbr);
	if (!((*data)->philo))
		return (free(*data), -1);
	gettime(data);
	if (init_philo(argc, argv, data) == -1)
		return (free(*data), free((*data)->philo), -1);
	if (pthread_create(&(*data)->monitor, NULL, &monitor_fun, *data) != 0)
		return (free(*data), free((*data)->philo), -1);
	pthread_mutex_lock(&(*data)->stop_lock);
	(*data)->ready = 1;
	pthread_mutex_unlock(&(*data)->stop_lock);
	return (1);
}
