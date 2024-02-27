/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:25 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 10:11:30 by tbolzan-         ###   ########.fr       */
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
	pthread_mutex_lock(philo->write);
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
	pthread_mutex_unlock(philo->write);
}

int	main(int ac, char **av)
{
	int		i;
	t_start	start;

	i = 0;
	if (validate_args(&start, av, ac) != 0)
		return (1);
	inicialize_arguments(av, &start);
	inicialize_all(&start);
	start.real_start_time = get_current_time();
	while (i < start.nbr_philo)
	{
		pthread_create(&start.philos[i].thread, NULL, &routine,
			&start.philos[i]);
		i++;
	}
	monitor(&start);
	i = 0;
	while (i < start.nbr_philo)
	{
		pthread_join(start.philos[i].thread, NULL);
		i++;
	}
	clean_mutex(&start);
	return (0);
}
