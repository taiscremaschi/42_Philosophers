/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:25 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/25 13:04:59 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers 1
// time_to_die 2
// time_to_eat 3
// time_to_sleep4
// [number_of_times_each_philosopher_must_eat]5

void	print_actions(t_philo *philo, int token)
{
	long int	current_time;

	current_time = get_current_time();
	if (is_over(philo) == 1)
		return ;
	if (token == 0)
		printf("%ld %d is thinking\n", current_time - *philo->start_time,
			philo->id);
	else if (token == 1)
	{
		printf("%ld %d has taken a fork\n", current_time - *philo->start_time,
			philo->id);
		printf("%ld %d has taken a fork\n", current_time - *philo->start_time,
			philo->id);
		printf("%ld %d is eating\n", current_time - *philo->start_time,
			philo->id);
	}
	else if (token == 2)
		printf("%ld %d is sleeping\n", current_time - *philo->start_time,
			philo->id);
	else if (token == 3)
		printf("%ld %d died\n", current_time - *philo->start_time, philo->id);
}

int	philo_is_dead(t_philo philo)
{
	if (philo.last_meal == 0)
		return (1);
	if (get_current_time() - philo.last_meal >= philo.time_die)
		return (0);
	return (1);
}

int	handle_dead(t_start *start)
{
	int	i;

	i = 0;
	while (i < start->nbr_philo)
	{
		if (philo_is_dead(start->philos[i]) == 1)
			i++;
		else
		{
		
        	print_actions(&start->philos[i], 3);
            pthread_mutex_lock(&start->monitor_mutex);    
			start->dead_flag = 1;
            pthread_mutex_unlock(&start->monitor_mutex);
			return (1);
		}
	}
	return (0);
}

int check_eatings(t_start *start, int nbr_eat)
{
    int	i;
    int nbrphilo = start->nbr_philo;
    
    i = 0;
    pthread_mutex_lock(&start->monitor_mutex);
    while(i < start->nbr_philo)
    {
        if (start->philos[i].nbr_eat_now >= nbr_eat)
		{
            i++;
        }
        else 
            break ;
    }
    if( i == nbrphilo)
    {
		start->dead_flag = 1;
        pthread_mutex_unlock(&start->monitor_mutex);
		return (1);
    }
    pthread_mutex_unlock(&start->monitor_mutex);
	return (0);
    
}

void	monitor(t_start *start)
{
    int nbr_eat = start->philos[0].nbr_eat;

    if(nbr_eat != -1)
    {
        while (1)
        {
            if (check_eatings(start, nbr_eat) == 1 || handle_dead(start) == 1)
                break ;
            usleep(500);
        }
        
    }
    else 
    {
        while (1)
        {
            if (handle_dead(start) == 1)
                break ;
        }
        
    }
}

int	main(int ac, char **av)
{
	int		i;
	t_start	start;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "number of wrong arguments\n", 26));
	inicialize_arguments(av, &start);
	inicialize_all(&start);
	start.real_start_time = get_current_time();
	while (i < start.nbr_philo)
	{
		pthread_create(&start.philos[i].thread, NULL, &routine,
			&start.philos[i]);
		i++;
	}
    printf("numero eat is %d\n", start.philos[i].nbr_eat);
	monitor(&start);
	i = 0;
	while (i < start.nbr_philo)
	{
		pthread_join(start.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
