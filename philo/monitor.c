/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:32:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 11:25:55 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_lock(&start->monitor_mutex);
		if (philo_is_dead(start->philos[i]) == 1)
			i++;
		else
		{
			pthread_mutex_unlock(&start->monitor_mutex);
			print_actions(&start->philos[i], 3);
			pthread_mutex_lock(&start->monitor_mutex);
			start->dead_flag = 1;
			pthread_mutex_unlock(&start->monitor_mutex);
			return (1);
		}
		pthread_mutex_unlock(&start->monitor_mutex);
	}
	return (0);
}

int	check_eatings(t_start *start, int nbr_eat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&start->monitor_mutex);
	if (start->philos[i].nbr_eat == -1)
	{
		pthread_mutex_unlock(&start->monitor_mutex);
		return (0);
	}
	while (i < start->nbr_philo)
	{
		if (start->philos[i].nbr_eat_now >= nbr_eat)
			i++;
		else
			break ;
	}
	if (i == start->nbr_philo)
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
	int	nbr_eat;

	nbr_eat = start->philos[0].nbr_eat;
	if (start->nbr_philo == 1)
	{
		start->dead_flag = 1;
		return ;
	}
	while (1)
	{
		if (check_eatings(start, nbr_eat) == 1 || handle_dead(start) == 1)
			break ;
	}
}
