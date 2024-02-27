/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 10:11:24 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(char *ptr)
{
	int	i;
	int	sig;
	int	result;

	sig = 1;
	result = 0;
	i = 0;
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-')
	{
		sig = sig * -1;
		i++;
	}
	else if (ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		result *= 10;
		result = result + ptr[i] - '0';
		i++;
	}
	return (sig * result);
}

void	clean_mutex(t_start *start)
{
	int	i;

	i = 0;
	while (i < start->nbr_philo)
	{
		pthread_mutex_destroy(&start->philos->fork_left);
		pthread_mutex_destroy(&start->philos->dead_mutex);
		i++;
	}
	pthread_mutex_destroy(&start->write_mutex);
	pthread_mutex_destroy(&start->monitor_mutex);
}
