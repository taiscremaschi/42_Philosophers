
#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

typedef struct s_philo
{
    pthread_mutex_t fork_left;
    pthread_mutex_t *fork_right;
    pthread_t thread;
    int id; 
    int nbr_eat_now;  
    pthread_mutex_t write; 
    pthread_mutex_t dead_mutex; 
    pthread_mutex_t meal_mutex;
    int time_die;  
    int time_eat;
    int time_sleep; 
    int nbr_time_eat;
    int *dead;
} t_philo;

typedef struct s_start 
{
    
    int nbr_philo;
    int dead_flag;
    t_philo *philos;

} t_start;

/////////////// utils /////////////////
unsigned int	ft_atoi(char *str);
int	ft_putstr(char *s);

/////////////// inicialize ///////////////

int inicialize_arguments(char **av, t_start *start);
void inicialize_all(t_start *start);


//////////////////// main ////////////////////



#endif