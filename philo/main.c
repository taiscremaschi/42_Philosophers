/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:25 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/23 17:41:04 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//number_of_philosophers 1
// time_to_die 2
//time_to_eat 3
//time_to_sleep4
// [number_of_times_each_philosopher_must_eat]5

void print_actions(t_philo *philo, int token)
{
    if(token == 0)
        printf("%ld %d is thinking\n", get_current_time() - philo->start_time, philo->id);
    else if (token == 1)
    {
        printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
        printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
        printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id);
    }
    else if (token == 2)
        printf("%ld %d is sleeping\n", get_current_time()- philo->start_time, philo->id);
    else if(token == 3)
        printf("%ld %d died\n", get_current_time()- philo->start_time, philo->id);
}

int is_over(t_philo *arg)
{
    pthread_mutex_lock(&arg->dead_mutex);
    if(*arg->dead == 1)
    {
        pthread_mutex_unlock(&arg->dead_mutex);
        return(1);
    }
    else
    {        
        pthread_mutex_unlock(&arg->dead_mutex);
        return(0);
    }
}
int wait_time(size_t milli, t_philo *philo)
{
	long int	start;

	start = get_current_time();
	while ((get_current_time() - start) < (long int)milli)
	{
        if(is_over(philo) == 1)
            return 1;
        usleep(500);
    }
        
	return (0);
}

int philo_sleep(t_philo *philo)
{
    print_actions(philo, 2);
    if (wait_time(philo->time_sleep, philo) == 1)
        return 1;
    print_actions(philo, 0);
    return (0);
}

int eat(t_philo *philo)
 {
    int flag = 0;
    if(philo->start_time == 0)
         philo->start_time = get_current_time();
    if(philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->fork_right);
        pthread_mutex_lock(&philo->fork_left);
    }
    else 
    {
        pthread_mutex_lock(&philo->fork_left);
        pthread_mutex_lock(philo->fork_right);
    }
    print_actions(philo, 1);
    philo->last_meal = get_current_time();
    philo->nbr_eat_now += 1;  
    flag = wait_time(philo->time_eat, philo);
    pthread_mutex_unlock(&philo->fork_left);
    pthread_mutex_unlock(philo->fork_right);
    return flag;
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;


    //enquanto minha dead flag na for um
    while(is_over(philo) == 0)
    {
        if (eat(philo) == 1)
            break ;
        if(philo_sleep(philo) == 1)
            break;
    }
    return (NULL);
}
int philo_is_dead(t_philo philo)
{
    if(philo.last_meal == 0)
        return 1;
        
    if(get_current_time() - philo.last_meal >= philo.time_die)
        return 0;
    return 1;
}

int handle_dead(t_start *start)
{
    int i =  0;

    while(i < start->nbr_philo)
    {
        if(philo_is_dead(start->philos[i]) == 1)
            i++;
        else
        {
            print_actions(&start->philos[i], 3);
            start->dead_flag = 1;
            return (1);
        }
    }
    return 0;
}
void monitor(t_start *start)
{
    while(1)
    {
        if(handle_dead(start) == 1)
            break ;
    }
}

int main(int ac, char **av)
{
    int i = 0;
    t_start start; 

    if(ac < 5 || ac > 6)
        return write(2, "number of wrong arguments\n", 26);
    inicialize_arguments(av, &start);
    inicialize_all(&start);

    while(i < start.nbr_philo)
    {
        pthread_create(&start.philos[i].thread, NULL, &routine, &start.philos[i]);
        i++;
    }
    monitor(&start);
    i = 0;
    while(i < start.nbr_philo)
    {
        pthread_join (start.philos[i].thread, NULL);
        i++;
    }
    

}
