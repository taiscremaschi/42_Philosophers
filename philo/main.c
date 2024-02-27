/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:25 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/27 10:19:02 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
