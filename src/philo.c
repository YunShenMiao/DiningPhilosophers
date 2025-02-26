/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:18 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/26 17:27:50 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Abweichung Zeit, eigene usleep?
// death_check within sleeping & eating usleep
// 1 philo
// starttime -> last_meal issue
// mutex lock on death
// maybe lock on init threads until all threads are initia;ized
// valgrind - hellgrind

// 2) go through code &subj pdf again before continue
// 3) protect memory
// 4) work on the philo_fun -> different functions, etc.:
// need to change philosopher dies, program ends
// need to know which philo access to which fork (for1, 2, 3etc)
//	+ generally mutext forkkram
// prcoesses stop as soon as one philo dies!!

#include "philo.h"

void	*monitor_fun(void *arg)
{
	t_data	*data;
	int		i;
	int		snacks;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		snacks = 0;
		while (i < data->philo_nbr)
		{
			if (data->philo[i].philo_died == 1)
				break ;
			if (data->philo[i].schnacks > 0 || data->philo[i].schnacks < 0)
				snacks = 1;
			i++;
		}
		if ((data->philo[i].philo_died == 1) || snacks == 0)
			break ;
	}
	i = -1;
	while (i++, i < data->philo_nbr)
		data->philo[i].philo_died = 1;
	return (NULL);
}

int	init_threads(t_data **data, int i)
{
	t_thread_data	*threaddata;

	threaddata = malloc(sizeof(t_thread_data));
	if (!threaddata)
		return (-1);
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
		(*data)->philo[i].philo_died = 0;
		(*data)->philo[i].fork = 0;
		(*data)->philo[i].eaten = 0;
		if (argc == 6)
			(*data)->philo[i].schnacks = ft_atoi(argv[5]);
		else
			(*data)->philo[i].schnacks = -2;
		if (init_threads(data, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_data(int argc, char *argv[], t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	gettime(data);
	(*data)->philo_nbr = ft_atoi(argv[1]);
	(*data)->gesnacked = 0;
	pthread_mutex_init(&(*data)->print_lock, NULL);
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nbr);
	if (!((*data)->philo))
		return (free(*data), -1);
	if (init_philo(argc, argv, data) == -1)
		return (free(*data), free((*data)->philo), -1);
	if (pthread_create(&(*data)->monitor, NULL, &monitor_fun, *data) != 0)
		return (free(*data), free((*data)->philo), -1);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments\n"), 1);
	if (init_data(argc, argv, &data) == -1)
		return (printf("Initialization error\n"), 1);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	pthread_join(data->monitor, NULL);
	pthread_mutex_destroy(&data->print_lock);
	free(data->philo);
	free(data);
	return (0);
}

/* void checkleak(void)
{
	system("leaks philo");
}
atexit(&checkleak); */