/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 11:17:33 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sig;
	int	result;

	sig = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sig = sig * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result = result + str[i] - '0';
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
		pthread_mutex_destroy(&start->philos[i].fork_left);
		pthread_mutex_destroy(&start->philos[i].dead_mutex);
		i++;
	}
	pthread_mutex_destroy(&start->write_mutex);
	pthread_mutex_destroy(&start->monitor_mutex);
}

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
