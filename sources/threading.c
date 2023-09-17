/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:29:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/17 14:38:13 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(pthread_t *checking, pthread_t *newt, t_vars *vars)
{
	int	i;

	i = 0;
	if (pthread_create(checking, NULL, &check_on_philos, vars))
		return (1);
	pthread_detach(*checking);
	vars->start_sim = get_time();
	while (i < vars->num_philo)
	{
		if (pthread_create(&newt[i], NULL, &philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_death(t_vars *vars, int i)
{
	int				j;
	struct timeval	tv;

	j = 0;
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(vars->alive);
	if (vars->philo[i].time_of_death + 5000
		<= (tv.tv_sec * 1000000 + tv.tv_usec))
	{
		vars->all_alive = 0;
		if (vars->all_full == 0)
		{
			printf("%ld %d died\n",
				get_time() - vars->start_sim, vars->philo[i].id);
		}
		while (j < vars->num_philo)
			pthread_mutex_unlock(&vars->forks[j++]);
		pthread_mutex_unlock(vars->alive);
		return (1);
	}
	pthread_mutex_unlock(vars->alive);
	return (0);
}

void	*check_on_philos(void *arg)
{
	t_vars			*vars;
	int				i;

	vars = (t_vars *)arg;
	while (vars->all_alive)
	{
		i = 0;
		while (i < vars->num_philo)
		{
			usleep(100);
			if (check_death(vars, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	*philosopher_dines(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (print_msg("is thinking", philo))
			return (NULL);
		if (take_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (ft_sleep(philo))
			return (NULL);
	}
	return (NULL);
}
