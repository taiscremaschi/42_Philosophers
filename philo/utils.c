/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:24:45 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/02/22 19:19:31 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int get_current_time()
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

unsigned int	ft_atoi(char *str)
{
    int i = 0;
    unsigned int result = 0;
    
    if(str[i] == ' ' || (str[i] >=  8 && str[i] <= 13))
        i++;
    if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
    {
        return write(2, "argument error\n", 15);
    }
    if(str[i] == '-')
    {
        return write(2, "argument error\n", 15);
    }    
    while(str[i] >= '0' && str[i] <= '9')
    {
        result *= 10;
        result =  result + str[i] - '0';
        i++;
    }

    return(result);
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
