/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:11:23 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 21:14:50 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_philo *arg)
{
	pthread_mutex_lock(arg->monitor_philo);
	if (*arg->dead == 1)
	{
		pthread_mutex_unlock(arg->monitor_philo);
		return (1);
	}
	pthread_mutex_unlock(arg->monitor_philo);
	return (0);
}

int	wait_time(size_t milli, t_philo *philo)
{
	long int	start;

	start = get_current_time();
	while ((get_current_time() - start) < (long int)milli)
	{
		if (is_over(philo) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_actions(philo, 2);
	if (wait_time(philo->time_sleep, philo) == 1)
		return (1);
	print_actions(philo, 0);
	usleep(500);
	return (0);
}

int	eat(t_philo *philo)
{
	int	flag;

	flag = 0;
	if (philo->id % 2 == 1)
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
	pthread_mutex_lock(philo->monitor_philo);
	philo->nbr_eat_now += 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->monitor_philo);
	flag = wait_time(philo->time_eat, philo);
	pthread_mutex_lock(philo->monitor_philo);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->monitor_philo);
	return (flag);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->n_philo == 1)
	{
		printf("%ld %d has taken a fork\n", get_current_time()
			- *philo->start_time, philo->id);
		usleep(philo->time_die * 1000);
		printf("%ld %d died\n", get_current_time() - *philo->start_time,
			philo->id);
		return (NULL);
	}
	if(philo->id % 2 != 0)
		usleep(100);
	while (is_over(philo) == 0)
	{
		if (eat(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
	}
	return (NULL);
}
