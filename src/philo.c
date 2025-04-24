/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:18 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/24 16:42:41 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// print messages after eaten enough times,
// eaten check sometimes work sometimes not?
// issue if deathtime is smaller eattime

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

int	check_input(int argc, char *argv[])
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (-1);
	}
	return (1);
}

int	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (-1);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->beg_stop_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->snack_lock);
	pthread_mutex_destroy(&data->full_lock);
	free(data->philo);
	free(data);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments\n"), 1);
	if (check_input(argc, argv) == -1)
		return (printf("invalid input\n"), 1);
	if (init_data(argc, argv, &data) == -1)
		return (printf("Initialization error\n"), 1);
	if (end_simulation(data) == -1)
		return (1);
	return (0);
}

/* void checkleak(void)
{
	system("leaks philo");
}
atexit(&checkleak); */