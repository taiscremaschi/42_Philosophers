/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:12 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/23 20:33:25 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	inicialize_all(t_start *start)
{
	int	i;

	i = 0;
	pthread_mutex_init(&start->end_mutex, NULL);
	while (i < start->nbr_philo)
	{
		pthread_mutex_init(&start->philos[i].write, NULL);
		pthread_mutex_init(&start->philos[i].dead_mutex, NULL);
		pthread_mutex_init(&start->philos[i].meal_mutex, NULL);
		pthread_mutex_init(&start->philos[i].fork_left, NULL);
		if (i == start->nbr_philo - 1)
			start->philos[i].fork_right = &start->philos[0].fork_left;
		else
			start->philos[i].fork_right = &start->philos[i + 1].fork_left;
		i++;
	}
}

int	inicialize_arguments(char **av, t_start *start)
{
	int	i;

	i = 0;
	start->nbr_philo = ft_atoi(av[1]);
	start->dead_flag = 0;
	while (i < start->nbr_philo)
	{
		start->philos[i].time_die = ft_atoi(av[2]);
		start->philos[i].time_eat = ft_atoi(av[3]);
		start->philos[i].time_sleep = ft_atoi(av[4]);
		if (start->philos[i].time_sleep == 0)
			return (write(2, "erro, o argumento nao pode ser 0\n", 33));
		start->philos[i].nbr_eat = -1;
		if (av[5])
			start->philos[i].nbr_eat = ft_atoi(av[5]);
		if (start->nbr_philo > 200 || start->nbr_philo <= 0)
			return (write(2, "erro nos filosofos\n", 19));
		if (start->philos[i].time_die <= 0 || start->philos[i].time_sleep <= 0
			|| start->philos[i].time_eat <= 0)
			return (write(2, "erro, o argumento nao pode ser 0\n", 33));
		start->philos[i].nbr_eat_now = 0;
		start->philos[i].id = i + 1;
		start->philos[i].dead = &start->dead_flag;
		start->philos[i].last_meal = 0;
		start->philos[i].start_time = &start->real_start_time;
		i++;
	}
	inicialize_forks(start->fork, start->nbr_philo);
	return (0);
}
