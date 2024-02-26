/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:39 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/26 19:48:26 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_NBR 200

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*write;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	*monitor_philo;
	int				id;
	int				nbr_eat_now;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	int				*dead;
	long int		last_meal;
	long int		*start_time;
}					t_philo;

typedef struct s_start
{
	int				nbr_philo;
	long int		real_start_time;
	int				dead_flag;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	fork[MAX_NBR];
	t_philo			philos[MAX_NBR];

}					t_start;

/////////////// utils /////////////////
int					ft_atoi(char *str);
long int			get_current_time(void);

/////////////// inicialize ///////////////
int					validate_args(t_start *start, char **av, int ac);
int					inicialize_arguments(char **av, t_start *start);
void				inicialize_all(t_start *start);

//////////////////// main ////////////////////
void				print_actions(t_philo *philo, int token);
int					philo_is_dead(t_philo philo);
int					handle_dead(t_start *start);
void				monitor(t_start *start);

////////////////////////routines///////////
int					philo_sleep(t_philo *philo);
int					eat(t_philo *philo);
void				*routine(void *arg);
int					is_over(t_philo *arg);
int					wait_time(size_t milli, t_philo *philo);

#endif