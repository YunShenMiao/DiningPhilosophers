/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:18 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/27 17:43:50 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int type)
{
	if (type == 1)
		write(2, "Wrong amount of arguments\n", 26);
	else if (type == 2)
		write(2, "Invalid input\n", 14);
	else
		write(2, "Initialization error\n", 21);
}

int	check_input(int argc, char *argv[])
{
	if (c_atoi(argv[1]) <= 0 || c_atoi(argv[2]) <= 0 || c_atoi(argv[3]) <= 0
		|| c_atoi(argv[4]) <= 0)
		return (-1);
	if (argc == 6)
	{
		if (c_atoi(argv[5]) < 0)
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
		return (print_error(1), 1);
	if (check_input(argc, argv) == -1)
		return (print_error(2), 1);
	start_message();
	if (init_data(argc, argv, &data) == -1)
		return (print_error(3), 1);
	if (end_simulation(data) == -1)
		return (1);
	return (0);
}

/* void checkleak(void)
{
	system("leaks philo");
}
atexit(&checkleak); */