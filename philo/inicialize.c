/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:12 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 10:11:36 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10)
			return (1);
		i++;
	}
	return (0);
}

void	inicialize_all(t_start *start)
{
	int	i;

	i = 0;
	pthread_mutex_init(&start->monitor_mutex, NULL);
	pthread_mutex_init(&start->write_mutex, NULL);
	while (i < start->nbr_philo)
	{
		pthread_mutex_init(&start->philos[i].dead_mutex, NULL);
		pthread_mutex_init(&start->philos[i].fork_left, NULL);
		start->philos[i].monitor_philo = &start->monitor_mutex;
		start->philos[i].write = &start->write_mutex;
		start->philos[i].n_philo = start->nbr_philo;
		if (i == start->nbr_philo - 1)
			start->philos[i].fork_right = &start->philos[0].fork_left;
		else
			start->philos[i].fork_right = &start->philos[i + 1].fork_left;
		i++;
	}
}

int	handle_valid_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_args(t_start *start, char **av, int ac)
{
	if (ac < 5 || ac > 6)
		return (write(2, "number of wrong arguments\n", 26));
	if (handle_valid_arg(av) == 1)
		return (write(2, "error in characters\n", 20));
	start->nbr_philo = ft_atoi(av[1]);
	if (start->nbr_philo > 200 || start->nbr_philo <= 0)
		return (write(2, "error in number of philos\n", 26));
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (write(2, "error\n", 6));
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (write(2, "error\n", 6));
	if (check_args(av) == 1)
		return (write(2, "error\n", 6));
	return (0);
}

int	inicialize_arguments(char **av, t_start *start)
{
	int	i;

	i = 0;
	start->dead_flag = 0;
	while (i < start->nbr_philo)
	{
		start->philos[i].time_die = ft_atoi(av[2]);
		start->philos[i].time_eat = ft_atoi(av[3]);
		start->philos[i].time_sleep = ft_atoi(av[4]);
		start->philos[i].nbr_eat = -1;
		if (av[5])
			start->philos[i].nbr_eat = ft_atoi(av[5]);
		start->philos[i].nbr_eat_now = 0;
		start->philos[i].id = i + 1;
		start->philos[i].dead = &start->dead_flag;
		start->philos[i].last_meal = 0;
		start->philos[i].start_time = &start->real_start_time;
		i++;
	}
	return (0);
}
