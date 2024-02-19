/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:39:12 by ricardo           #+#    #+#             */
/*   Updated: 2023/12/19 18:03:17 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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

