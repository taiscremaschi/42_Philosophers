/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:32:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/26 12:33:14 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_eatings(t_start *start, int nbr_eat)
{
	int	i;
	int	nbrphilo;

	nbrphilo = start->nbr_philo;
	i = 0;
	pthread_mutex_lock(&start->monitor_mutex);
	while (i < start->nbr_philo)
	{
		if (start->philos[i].nbr_eat_now >= nbr_eat)
		{
			i++;
		}
		else
			break ;
	}
	if (i == nbrphilo)
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
	if (nbr_eat != -1)
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
