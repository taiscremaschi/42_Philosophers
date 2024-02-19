/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:21 by ricardo           #+#    #+#             */
/*   Updated: 2023/12/19 18:26:44 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void inicialize_all(t_start *start)
{
    int i = 0;
    
    while(i < start->nbr_philo)
    {
        printf("%d\n", i);
        pthread_mutex_init(&start->philos[i].write, NULL);
        pthread_mutex_init(&start->philos[i].dead_mutex, NULL);
        pthread_mutex_init(&start->philos[i].meal_mutex, NULL);
        pthread_mutex_init(&start->philos[i].fork_left, NULL);
        
        if(i == start->nbr_philo - 1)
            start->philos[i].fork_right = &start->philos[0].fork_left;
        else 
            start->philos[i].fork_right = &start->philos[i + 1].fork_left;
        i++;
    }
}

int inicialize_arguments(char **av, t_start *start)
{
    int i;

    i = 0;
    start->nbr_philo = ft_atoi(av[1]);

    start->philos = malloc(sizeof(t_philo) * (start->nbr_philo + 1));
    start->dead_flag = 0;
    while(i < start->nbr_philo)
    {
        start->philos[i].time_die = ft_atoi(av[2]);
        start->philos[i].time_eat = ft_atoi(av[3]);
        start->philos[i].time_sleep = ft_atoi(av[4]);
        if(start->philos[i].time_sleep == 0)
            return write(2, "erro, o argumento nao pode ser 0\n", 33);
        start->philos[i].nbr_time_eat = -1;
        if(av[5])
            start->philos[i].nbr_time_eat = ft_atoi(av[5]);
        if(start->nbr_philo > 200 || start->nbr_philo <= 0)
            return write(2, "erro nos filosofos\n", 19);
        if(start->philos[i].time_die <= 0 || start->philos[i].time_sleep <= 0 || start->philos[i].time_eat <= 0) 
            return write(2, "erro, o argumento nao pode ser 0\n", 33);
        start->philos[i].nbr_eat_now = 0;
        start->philos[i].id = i;
        start->philos[i].dead = &start->dead_flag;
        i++;
    }
    return (0);
}
