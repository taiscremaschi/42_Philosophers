/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/26 11:57:15 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(const char *ptr)
{
	int	x;
	int	signal;
	int	result;

	signal = 1;
	result = 0;
	x = 0;
	while (ptr[x] == ' ' || (ptr[x] >= 9 && ptr[x] <= 13))
		x++;
	if (ptr[x] == '-')
	{
		signal = signal * -1;
		x++;
	}
	else if (ptr[x] == '+')
		x++;
	while (ptr[x] >= '0' && ptr[x] <= '9')
	{
		result *= 10;
		result = result + ptr[x] - '0';
		x++;
	}
	return (signal * result);
}

void	ft_putchar_fd(char c)
{
	write(1, &c, 1);
}

int	ft_putstr(char *s)
{
	int	x;

	x = 0;
	while (s[x] != '\0')
		ft_putchar_fd(s[x++]);
	return (x);
}
