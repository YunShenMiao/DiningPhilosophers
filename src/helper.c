/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:20:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/04/27 17:41:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_string(const char *str, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_lock);
	if (forever_schleepi(data) != -1)
		printf("%ld %d %s\n", current_time(philo), philo->id, str);
	pthread_mutex_unlock(&data->print_lock);
}

int	ft_usleep(t_philo *philo, long sleep)
{
	long	start;

	start = current_time(philo);
	while ((current_time(philo) - start) < sleep)
	{
		usleep(100);
	}
	return (1);
}

void	gettime(t_data **data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	(*data)->starttime = start_time;
}

long	current_time(t_philo *philo)
{
	struct timeval	current_time;
	long			ms;

	gettimeofday(&current_time, NULL);
	ms = ((current_time.tv_sec - philo->starttime.tv_sec) * 1000
			+ (current_time.tv_usec - philo->starttime.tv_usec) / 1000);
	return (ms);
}

int	c_atoi(const char *str)
{
	int	count;
	int	cneg;
	int	res;

	count = 0;
	cneg = 1;
	res = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n'
		|| str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
		count++;
	if (str[count] == '-')
		cneg = -1;
	if (str[count] == '+' || str[count] == '-')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		res = res * 10 + (str[count] - '0');
		count++;
	}
	if (str[count] != '\0')
		return (-1);
	if (cneg == -1)
		res = res * cneg;
	return (res);
}
