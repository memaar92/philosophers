/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:38:53 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/02 14:24:18 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

t_vars *alloc_mem(int num_philo)
{
	t_vars	*vars;
	
	vars = malloc(sizeof(*vars));
	if (!vars)
		return (NULL);
	vars->forks = malloc(num_philo * sizeof((*(vars->forks))));
	if (!(vars->forks))
		return (NULL);
	vars->philo = malloc(num_philo * sizeof(*(vars->philo)));
	if (!(vars->philo))
		return (NULL);
	return (vars);
}

void	set_static_vars(t_vars *vars)
{
	vars->time_to_die = 300;
	vars->time_to_eat = 10;
	vars->time_to_sleep = 50;
	vars->all_alive = 1;
}

int	init_philos(t_vars *vars, int num_philo)
{
	int	i;
	struct timeval	tv;
	long			time;

	i = 0;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	while (i < num_philo)
	{
		//set all vars to 0/NULL
		vars->philo[i].vars = vars;
		vars->philo[i].id = i + 1;
		vars->philo[i].time_of_death = time + 10000000;
		vars->philo[i].count_philo = num_philo;
		vars->philo[i].left_fork = &vars->forks[i];
		if (i + 1 == num_philo)
			vars->philo[i].right_fork = &vars->forks[0];
		else
			vars->philo[i].right_fork = &vars->forks[i + 1];
		i++;
	}
	return (0);
}


t_vars *init_structs(int num_philo) // add args for time to die/eat/sleep
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = alloc_mem(num_philo);
	if (!vars)
		return (NULL);
	set_static_vars(vars);
	while (i < num_philo)
		pthread_mutex_init(&vars->forks[i++], NULL);
	init_philos(vars, num_philo);
	return (vars);
}
