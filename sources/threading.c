/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:29:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/05 10:56:20 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(pthread_t *checking, pthread_t *newthread, t_vars *vars, int argc)
{
	int			i;
	pthread_t	*checking2;

	i = 0;
	checking2 = malloc(sizeof(*checking2));
	if (!checking2)
		return (1);
	if (pthread_create(checking, NULL, check_on_philos, vars))
		return (free(checking2), 1);
	pthread_detach(*checking); // detach thread?
	if (argc == 6)
	{
		if (pthread_create(checking2, NULL, check_philos_full, vars))
			return (free(checking2), 1);
		pthread_detach(*checking2); // detach thread?
	}
	free(checking2);
	vars->start_sim = calc_start_time();
	while (i < vars->num_philo)
	{
		if (pthread_create(&newthread[i], NULL, philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*check_philos_full(void *arg)
{
	t_vars	*vars;
	int		i;
	int		j;

	vars = (t_vars *)arg;
	j = 0;
	while (!(vars->all_full))
	{
		i = 0;
		while (i < vars->num_philo && vars->philo[i].meals_eaten >= vars->num_meals)
			i++;
		if (i == vars->num_philo)
		{
			vars->all_full = 1;
			while (j < vars->num_philo)
				pthread_mutex_unlock(&vars->forks[j++]);
			return (NULL);
		}
	}
	return (NULL);
}


void	*check_on_philos(void *arg)
{
	t_vars			*vars;
	struct timeval	tv;
	int				i;
	int				j;

	vars = (t_vars *)arg;
	j = 0;
	while (vars->all_alive)
	{
		i = 0;
		while (i < vars->num_philo)
		{
			pthread_mutex_lock(vars->alive);
			gettimeofday(&tv, NULL);
			if (vars->philo[i].time_of_death <= (tv.tv_sec * 1000000 + tv.tv_usec))
			{
				vars->all_alive = 0;
				printf("%ld %d died\n", get_timestamp(vars->philo), vars->philo[i].id);
				while (j < vars->num_philo)
					pthread_mutex_unlock(&vars->forks[j++]);
				pthread_mutex_unlock(vars->alive);
				return (NULL);
			}
			pthread_mutex_unlock(vars->alive);
			ft_usleep(1);
			i++;
		}
	}
	return (NULL);
}

void	*philosopher_dines(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->vars->all_alive && !(philo->vars->all_full))
	{
		pthread_mutex_lock(philo->vars->alive);
		if (!(philo->vars->all_alive) || philo->vars->all_full)
			return (pthread_mutex_unlock(philo->vars->alive), NULL);
		printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(philo->vars->alive);
		// if (philo->id % 2 == 0)
		// 	ft_usleep(philo->vars->time_to_eat / 2);
		if (philo->id % 2 != 0 && philo->meals_eaten == 0)
			ft_usleep(philo->vars->time_to_eat / 2);
		if (take_forks(philo))
			return (pthread_mutex_unlock(philo->vars->alive), NULL);
		if (eat(philo))
			return (pthread_mutex_unlock(philo->vars->alive), NULL);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (ft_sleep(philo))
			return (pthread_mutex_unlock(philo->vars->alive), NULL);
	}
	return (NULL);
}
