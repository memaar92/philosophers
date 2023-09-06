/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:56:57 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/06 15:26:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (print_msg("has taken a fork", philo))
		return (1);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (print_msg("has taken a fork", philo))
		return (1);
	return (0);
}

int	increment_num_meals(t_philo *philo)
{
	int	i;

	i = 0;
	philo->meals_eaten++;
	while (i < philo->vars->num_philo 
		&& philo->vars->philo[i].meals_eaten >= philo->vars->num_meals)
		i++;
	if (i == philo->vars->num_philo)
	{
		philo->vars->all_full = 1;
		i = 0;
		while (i < philo->vars->num_philo)
			pthread_mutex_unlock(&philo->vars->forks[i++]);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	struct timeval	tv;

	if (print_msg("is eating", philo))
		return (1);
	pthread_mutex_lock(philo->vars->alive);
	gettimeofday(&tv, NULL);
	philo->time_of_death = (tv.tv_sec * 1000000 + tv.tv_usec 
		+ (philo->vars->time_to_die * 1000));
	pthread_mutex_unlock(philo->vars->alive);
	ft_usleep(philo->vars->time_to_eat);
	pthread_mutex_lock(philo->vars->alive);
	if (philo->vars->num_meals != -1)
	{
		if (increment_num_meals(philo))
			return (1);
	}
	pthread_mutex_unlock(philo->vars->alive);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (print_msg("is sleeping", philo))
		return (1);
	ft_usleep(philo->vars->time_to_sleep);
	return (0);
}
