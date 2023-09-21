/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:29:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/21 10:41:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(pthread_t *checking, pthread_t *newt, t_vars *vars)
{
	int	i;

	i = 0;
	pthread_mutex_init(&vars->flag, NULL);
	pthread_mutex_lock(&vars->flag);
	while (i < vars->num_philo)
	{
		if (pthread_create(&newt[i], NULL, &philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	vars->start_sim = get_time();
	pthread_mutex_unlock(&vars->flag);
	if (pthread_create(checking, NULL, &check_on_philos, vars))
		return (1);
	pthread_detach(*checking);
	return (0);
}

int	check_death(t_vars *vars, int i)
{
	struct timeval	tv;

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
	while (1)
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

void	init_time_of_death(t_philo *philo)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	philo->time_of_death = time + (philo->vars->time_to_die * 1000);
}

void	*philosopher_dines(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	init_time_of_death(philo);
	pthread_mutex_lock(&philo->vars->flag);
	pthread_mutex_unlock(&philo->vars->flag);
	if (philo->id % 2 == 0)
	{
		if (print_msg("is thinking", philo))
			return (NULL);
		ft_usleep(philo->vars->time_to_eat / 2);
	}
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (ft_sleep(philo))
			return (NULL);
		if (print_msg("is thinking", philo))
			return (NULL);
	}
}
