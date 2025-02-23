/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:59 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/23 18:03:18 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
    pthread_t       thread;
    int             tt_sleep;
    int             tt_eat;
    int             tt_die;
    int             schnacks;
    int             id;
    int             forks;
    struct timeval  starttime;
    long            lastmeal;
}           t_philo;   

typedef struct s_data
{
    t_philo         *philo;
    int             philo_nbr;
    int             philo_current;
    struct timeval  starttime;
}              t_data;

//helper
int	    ft_atoi(const char *str);
char	*ft_itoa(int n);
void    free_threads(t_data **data);
char	*ft_strdup(const char *src);
void    *philo_fun(void* arg);


#endif