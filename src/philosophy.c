/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/23 18:21:22 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat -> sleep -> think

long current_time(t_philo *philo)
{
    struct timeval current_time;
    long ms;
    
    gettimeofday(&current_time, NULL);
    printf("miao: %ld  %ld\n", philo->starttime.tv_usec, current_time.tv_usec);
    ms = ((current_time.tv_sec - philo->starttime.tv_sec) * 1000
        + (current_time.tv_usec - philo->starttime.tv_usec) / 1000);
    return(ms);
}

int forever_schleepi(t_philo *philo)
{
    printf("%ld [ms]: Philo %d died\n", current_time(philo), philo->id);
}

int thinky(t_philo *philo)
{
    printf("%ld [ms]: Philo %d is thinking\n", current_time(philo), philo->id);
}


int schleepi(t_philo *philo)
{
    int sleeptime;

    sleeptime = philo->tt_sleep * 1000;
    printf("%ld [ms]: Philo %d is sleeping\n", current_time(philo), philo->id);
    usleep(sleeptime);
}

int schnacki(t_philo *philo)
{
    int schnacktime;

    schnacktime = philo->tt_eat * 1000;
    //check for forks
    // take forks if available 
    printf("%ld [ms]: Philo %d is eating\n", current_time(philo), philo->id);
    usleep(schnacktime);
    philo->lastmeal = current_time(philo);
    
}

void* philo_fun(void* arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;
    while(1)
    {
    if()
    schnacki(philo); // if check
    else
    {
    schleepi(philo);
    thinky(philo);
    }
    printf("hallo %ld, %ld, %ld", philo->lastmeal, (long)philo->tt_die, current_time(philo));
    if (philo->lastmeal + (long)philo->tt_die < current_time(philo))
    {
    forever_schleepi(philo);
    break;
    }
    }
   /*  pthread_t thread_id = pthread_self(); */
   /*  printf("Philo: %d, tt_sleep %d, tt_eat %d, tt_die %d meals %d\n", philo->id, philo->tt_sleep, philo->tt_eat, philo->tt_die, philo->schnacks); */
    return(NULL);
}