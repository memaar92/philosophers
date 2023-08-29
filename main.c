/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/29 15:15:51 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

// pthread_mutex_t	*forks;

int get_timestamp() // 1000 microsec are 1 millisec
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return(tv.tv_usec / 1000);
}

t_vars *init_vars(int num_philo) // add args for time to die/eat/sleep
{
	int		i;
	int		j;
	t_vars	*vars;

	i = 0;
	vars = malloc(sizeof(*vars));
	if (!vars)
		return (NULL);

	vars->time_to_die = 300;
	vars->time_to_eat = 10;
	vars->time_to_sleep = 50;
	vars->forks = malloc(num_philo * sizeof((*(vars->forks))));
	if (!(vars->forks))
		return (NULL);
	vars->philo = malloc(num_philo * sizeof(*(vars->philo)));
	if (!(vars->philo))
		return (NULL);
	while (i < num_philo)
		pthread_mutex_init(&vars->forks[i++], NULL);
	
	i = 0;
	while (i < num_philo)
	{
		vars->philo[i].id = i + 1;
		vars->philo[i].count_philo = num_philo;
		vars->philo[i].left_fork = &vars->forks[i];
		if (i + 1 == num_philo)
			vars->philo[i].right_fork = &vars->forks[0];
		else
			vars->philo[i].right_fork = &vars->forks[i + 1];
		i++;
	}
	return (vars);
}


void	*philosopher_dines(void *arg) // probably philo id as argument; also needs info about time to eat etc.
{
	t_philo *philo = (t_philo *)arg;
	int	left;
	int	right;

	left = philo->id - 1;
	if (philo->id == philo->count_philo)
		right = 0;
	else
		right = philo->id;
	while (1) // also stop if all philos have eaten at least x times (provided as argument)
	{
		if (philo->id % 2 != 0)
		{
			// check if fork is logged, if not, take the left fork
			pthread_mutex_lock(philo->left_fork);
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, left);
			usleep(5000000);

			// check if fork is logged, if not, take the right fork
			pthread_mutex_lock(philo->right_fork);
			printf("%d: Philosopher %d has taken taken fork %d\n", get_timestamp(), philo->id, right);
		}
		else if (philo->id % 2 == 0)
		{
			// check if fork is logged, if not, take the right fork
			pthread_mutex_lock(philo->right_fork);
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, right);
			
			// check if fork is logged, if not, take the left fork
			pthread_mutex_lock(philo->left_fork);
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, left);
		}
		// if philo has two forks taken up, philo eats for X milliseconds (provided as argument); use usleep?
		printf("%d: Philosopher %d is eating\n", get_timestamp(), philo->id);
		usleep(1000000); // takes microseconds 1000000ms = 1sec
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// once philo has finished eating, unlock the used forks

		//start sleeping for X milliseconds (provided as argument); use usleep?
		printf("%d: Philosopher %d is sleeping\n", get_timestamp(), philo->id);
		usleep(1000000);

		printf("%d: Philosopher %d is thinking\n", get_timestamp(), philo->id);
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	t_vars		*vars;
	int			num_philo = 2;
	int			i;

	i = 0;
	newthread = malloc(num_philo * sizeof(*newthread));
	if (!newthread)
		return (1);
	vars = init_vars(num_philo);
	if (!vars)
		return (1);
	// forks = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(&forks[0], NULL);
	// pthread_mutex_init(&forks[1], NULL);
	
	while (i < num_philo)
	{
		// create threads for each philosopher (number is given by argv[1]; struct for each philo?)
		if (pthread_create(&newthread[i], NULL, philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(newthread[i], NULL))
			return (1);
		pthread_mutex_destroy(&(vars->forks[i]));
		i++;
	}
}