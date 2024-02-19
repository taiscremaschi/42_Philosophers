
#include "philo.h"
# define MAX_NBR 200
//checar se tem min 1 filosofo, e se tiver 1 ele tem que morrer. 
//number_of_philosophers 1
// time_to_die 2
//time_to_eat 3
//time_to_sleep4
// [number_of_times_each_philosopher_must_eat]5



void inicialize_philos()
{

}

void	inicialize_forks(pthread_mutex_t *fork, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}
void* routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    return (NULL);
}

int main(int ac, char **av)
{
    int i = 0;
    //pthread_mutex_t fork[MAX_NBR];
    //pthread_t  *thread;
    //t_philo philo[MAX_NBR];
    t_start start; 

    if(ac < 5 || ac > 6)
        return write(2, "number of wrong arguments\n", 26);
    
    inicialize_arguments(av, &start);
    inicialize_all(&start);

    while(i <= start.nbr_philo)
    {
        pthread_create(&start.philos[i].thread, NULL, &routine, &start.philos[i]);
        i++;
    }

}
