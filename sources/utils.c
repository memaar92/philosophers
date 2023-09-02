/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:40:48 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/02 16:39:16 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (sign * result);
}

int	ft_usleep(int wait)
{
	struct timeval	tv;
	long			time;
	long			time2;
	
	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
	time2 = time + (wait / 1000) - 1;
	while (time <= time2)
	{
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
	}
	return(0);
}
