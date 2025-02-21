/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:31:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/21 17:26:11 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int forever_schleepi()
{
    
}

int thinky()
{
    
}

int schleepi()
{
    
}

int schnacki()
{
    
}

void* philo_fun(void* arg)
{
    t_philo *philo;
    
    philo = (t_philo*)arg;
/*     if()
    schnacki() // take fork + fork, eat

    else if()
    schleepi()

    else if()
    thinky()

    else if()
    forever_schleepi()
    
    
    pthread_t thread_id = pthread_self(); */
    printf("Philo: %d, tt_sleep %d, tt_eat %d, tt_die %d\n", philo->id, philo->tt_sleep, philo->tt_eat, philo->tt_die);
    return(NULL);
}