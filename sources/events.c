/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:56:57 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/03 18:22:38 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork_even_philo(t_philo *philo, int left, int right) // rm left and right ints
{
	pthread_mutex_lock(philo->right_fork);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, right);
	pthread_mutex_lock(philo->left_fork);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, left);
	return (0);
}

int	take_fork_uneven_philo(t_philo *philo, int left, int right) // rm left and right ints
{
	pthread_mutex_lock(philo->left_fork);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, left);
	pthread_mutex_lock(philo->right_fork);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, right);
	return (0);
}

int	take_forks(t_philo *philo)
{
	int	left; // definition of left and right for testing purposes
	int	right;

	left = philo->id - 1;
	if (philo->id == philo->count_philo)
		right = 0;
	else
		right = philo->id;
	if (philo->id % 2 != 0)
	{
		if (take_fork_uneven_philo(philo, left, right))
			return (1);
	}
	else if (philo->id % 2 == 0)
	{
		if (take_fork_even_philo(philo, left, right))
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	struct timeval	tv;

	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d is eating\n", get_timestamp(philo), philo->id);
	gettimeofday(&tv, NULL);
	philo->time_of_death = tv.tv_sec * 1000000 + tv.tv_usec + (philo->vars->time_to_die * 1000);
	ft_usleep(philo->vars->time_to_eat);
	philo->meals_eaten++;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (1);
	printf("%ld: Philosopher %d is sleeping\n", get_timestamp(philo), philo->id);
	ft_usleep(philo->vars->time_to_sleep);
	return (0);
}
