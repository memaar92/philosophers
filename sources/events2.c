/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:32:13 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/05 14:32:44 by mamesser         ###   ########.fr       */
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
