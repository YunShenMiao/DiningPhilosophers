/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:20:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/26 16:52:48 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_string(char *str, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %d %s\n", current_time(philo), philo->id, str);
	pthread_mutex_unlock(&data->print_lock);
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

// converts str to int skipping ws 1+ or -
int	ft_atoi(const char *str)
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
	{
		cneg = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		res = res * 10 + (str[count] - '0');
		count++;
	}
	if (cneg == -1)
		res = res * cneg;
	return (res);
}
