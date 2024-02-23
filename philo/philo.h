/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:39 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/23 12:12:06 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_NBR 200

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

typedef struct s_philo
{
    pthread_t thread;
    pthread_mutex_t fork_left;
    pthread_mutex_t *fork_right;
    pthread_mutex_t write; 
    pthread_mutex_t dead_mutex; 
    pthread_mutex_t meal_mutex;
    int id; 
    int nbr_eat_now;  
    int time_die;  
    int time_eat;
    int time_sleep; 
    int nbr_eat;
    int *dead;
    long int last_meal;
    long int start_time;
} t_philo;

typedef struct s_start 
{
    
    int nbr_philo;
    int dead_flag;
    pthread_mutex_t end_mutex;
    pthread_mutex_t fork[MAX_NBR];
    t_philo philos[MAX_NBR];

} t_start;

/////////////// utils /////////////////
unsigned int	ft_atoi(char *str);
int	ft_putstr(char *s);
long int get_current_time();


/////////////// inicialize ///////////////

int inicialize_arguments(char **av, t_start *start);
void inicialize_all(t_start *start);


//////////////////// main ////////////////////



#endif