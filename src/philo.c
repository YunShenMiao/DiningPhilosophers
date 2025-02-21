/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:18 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/21 17:29:05 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// printf("miao1\n");
// first initialization on philo, need to:
// 1) check everything with my prints
// 2) go through code &subj pdf again before continue
// 3) protect memory
// 4) work on the philo_fun -> different functions, etc.

#include "philo.h"

int init_philo(int argc, char *argv[], t_data **data)
{
    int i;
    
    *data = malloc(sizeof(t_data));
    if(!(*data))
    return(-1);
    (*data)->philo_nbr = ft_atoi(argv[1]);
    (*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nbr);
    if(!((*data)->philo))
    return(free(data), -1);
    i = 0;
    while (i < (*data)->philo_nbr)
    {
    (*data)->philo[i].id = i + 1;
    (*data)->philo[i].tt_die = ft_atoi(argv[2]);
    (*data)->philo[i].tt_eat = ft_atoi(argv[3]);
    (*data)->philo[i].tt_sleep = ft_atoi(argv[4]);
    if(argc == 6)
    (*data)->philo[i].schnacks = ft_atoi(argv[5]);
    else
    (*data)->philo[i].schnacks = -1;
    (*data)->philo_current = i;
     if (pthread_create(&(*data)->philo[i].thread, NULL, philo_fun, &(*data)->philo[i]) != 0)
        return(free_threads((*data)->philo), -1);
    i++;
    }
    return(0);
}

int main(int argc, char *argv[])
{
    t_data  *data;
    int i;
    
    
    if (argc < 5 || argc > 6)
    return(printf("Wrong amount of arguments\n"), 1);
    init_philo(argc, argv, &data);
    printf("total amount philo: %d\n", data->philo_nbr);
    i = 0;
    while(i < data->philo_nbr)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }

    /* free_threads(&data); */
    return(0);
}