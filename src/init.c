/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:45:16 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/27 17:46:11 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_message(void)
{
	printf("        _\n");
	printf("       |-|\n");
	printf("       |~|\n");
	printf("       |:|   DINING\n");
	printf("      .'.'.     PHILOSOPHERS\n");
	printf("     /   ::\\\n");
	printf("     |_____|     __          _\n");
	printf("     |:.:;.|   <:__:>     .-'o\\\n");
	printf("     |_____|   \\  ::/  .o' O. o\\\n");
	printf("     |   ::|    '..'  |--o.--o--|\n");
	printf("     |   ;:|     ||   |._._o_._.|\n");
	printf("     \\_____/    .''.\n");
	printf("               '----'\n\n");
	printf("\033[32mLOADING ...\n\033[0m");
	usleep(1500000);
	printf("\n");
}

int	init_threads(t_data **data, int i)
{
	t_philo_con	*philocontext;

	philocontext = malloc(sizeof(t_philo_con));
	if (philocontext == NULL)
		return (-1);
	philocontext->data = (*data);
	philocontext->philo = &(*data)->philo[i];
	if (pthread_create(&(*data)->philo[i].thread, NULL, &philo_fun,
			philocontext) != 0)
		return (free(philocontext), -1);
	return (1);
}

int	init_philo(int argc, char *argv[], t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nbr)
	{
		pthread_mutex_init(&(*data)->philo[i].lock, NULL);
		(*data)->philo[i].starttime = (*data)->starttime;
		(*data)->philo[i].lastmeal = current_time((*data)->philo);
		(*data)->philo[i].id = i + 1;
		(*data)->philo[i].tt_die = c_atoi(argv[2]);
		(*data)->philo[i].tt_eat = c_atoi(argv[3]);
		(*data)->philo[i].tt_sleep = c_atoi(argv[4]);
		(*data)->philo[i].own_fork = 0;
		(*data)->philo[i].righty_fork = 0;
		if (argc == 6)
			(*data)->philo[i].schnacks = c_atoi(argv[5]);
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
	(*data)->philo_nbr = c_atoi(argv[1]);
	(*data)->full = 0;
	(*data)->beg_stop = 0;
	pthread_mutex_init(&(*data)->print_lock, NULL);
	pthread_mutex_init(&(*data)->meal_lock, NULL);
	pthread_mutex_init(&(*data)->full_lock, NULL);
	pthread_mutex_init(&(*data)->snack_lock, NULL);
	pthread_mutex_init(&(*data)->beg_stop_lock, NULL);
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nbr);
	if (!((*data)->philo))
		return (free(*data), -1);
	gettime(data);
	if (init_philo(argc, argv, data) == -1)
		return (free(*data), free((*data)->philo), -1);
	if (pthread_create(&(*data)->monitor, NULL, &monitor_fun, *data) != 0)
		return (free(*data), free((*data)->philo), -1);
	pthread_mutex_lock(&(*data)->beg_stop_lock);
	(*data)->beg_stop = 1;
	pthread_mutex_unlock(&(*data)->beg_stop_lock);
	return (1);
}
