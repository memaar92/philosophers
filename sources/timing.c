/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:53:29 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/03 16:23:02 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_timestamp(t_philo *philo) // 1000 microsec are 1 millisec
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000) - philo->vars->start_sim;
	return (time);
}

long	calc_start_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec) / 1000;
	return (time);
}

int	ft_usleep(int wait)
{
	struct timeval	tv;
	long			time;
	long			time2;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
	time2 = time + wait;
	while (time < time2)
	{
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
	}
	return (0);
}

// alternative approach to create usleep
// void	start_action(t_philosopher *philo, int duration)
// {
// 	long	start_time;

// 	start_time = gettime();
// 	while (gettime() - start_time < duration)
// 	{
// 		if (stop_sim(philo->pd) == true)
// 			break ;
// 	}
// }