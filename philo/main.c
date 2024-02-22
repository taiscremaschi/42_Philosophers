/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:25 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/22 11:09:04 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//number_of_philosophers 1
// time_to_die 2
//time_to_eat 3
//time_to_sleep4
// [number_of_times_each_philosopher_must_eat]5
long int get_time_philo()
{
    struct timeval time_initial;
    
    gettimeofday(&time_initial, NULL);
    return (time_initial.tv_sec * 1000 + time_initial.tv_usec / 1000);
}

void print_actions(t_philo *philo, int token)
{
    if(token == 0)
        printf("%ld %d is thinking\n",get_time_philo(), philo->id);
    else if (token == 1)
    {
        printf("%ld %d has taken a fork\n",get_time_philo(), philo->id);
        printf("%ld %d has taken a fork\n",get_time_philo(), philo->id);
        printf("%ld %d is eating\n",get_time_philo(), philo->id);
    }
    else if (token == 2)
        printf("%ld %d is sleeping\n",get_time_philo(), philo->id);
    else if(token == 3)
        printf("%ld %d died\n",get_time_philo(), philo->id);
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
void philo_sleep(t_philo *philo, size_t milli)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milli)
		usleep(500);
	return (0);
    print_actions(philo, 2);
    usleep(philo->time_sleep * 1000);
    
}
void eat(t_philo *philo)
 {
    pthread_mutex_lock(&philo->fork_left);
    pthread_mutex_lock(philo->fork_right);
    print_actions(philo, 1);
    usleep(philo->time_eat * 1000);
  //  checar se esta morto caso estiver mudaqr a flag
//    atualizar o tempo de vida

    pthread_mutex_unlock(&philo->fork_left);
    pthread_mutex_unlock(philo->fork_right);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    //começam pensando 
    //comem obeservar os garfos enquanto o 1 come o dois nao pode comer 
    // enquanto comem n podem pensar nem dormir
    //dormem 
    //voltam a pensar ate voltar a comer 
    //enquanto minha dead flag na for um
    while(is_over(philo) == 0)
    {
        eat(philo);
        philo_sleep(philo);
      //think();  
    }
    return (NULL);
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
    i = 0;
    while(i < start.nbr_philo)
    {
        pthread_join (start.philos[i].thread, NULL);
        i++;
    }
    

}
