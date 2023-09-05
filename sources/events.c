/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:56:57 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/05 13:48:11 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork_even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	pthread_mutex_unlock(philo->vars->alive);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	pthread_mutex_unlock(philo->vars->alive);
	return (0);
}

int	take_fork_uneven_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	pthread_mutex_unlock(philo->vars->alive);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	pthread_mutex_unlock(philo->vars->alive);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (take_fork_uneven_philo(philo))
			return (1);
	}
	else if (philo->id % 2 == 0)
	{
		if (take_fork_even_philo(philo))
			return (1);
	}
	return (0);
}

int	increment_num_meals(t_philo *philo)
{
	int	i;

	i = 0;
	philo->meals_eaten++;
	while (i < philo->vars->num_philo && philo->vars->philo[i].meals_eaten >= philo->vars->num_meals)
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
	
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d is eating\n", get_timestamp(philo), philo->id);
	gettimeofday(&tv, NULL);
	philo->time_of_death = tv.tv_sec * 1000000 + tv.tv_usec + (philo->vars->time_to_die * 1000);
	if (philo->vars->num_meals != -1)
	{
		if (increment_num_meals(philo))
			return (1);
	}
	pthread_mutex_unlock(philo->vars->alive);
	ft_usleep(philo->vars->time_to_eat);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld %d is sleeping\n", get_timestamp(philo), philo->id);
	pthread_mutex_unlock(philo->vars->alive);
	ft_usleep(philo->vars->time_to_sleep);
	return (0);
}
