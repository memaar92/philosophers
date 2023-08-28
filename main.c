/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/28 16:24:01 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"


int get_timestamp() // 1000 microsec are 1 millisec
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return(tv.tv_usec / 1000);
}

t_vars *init_vars(int num_philo) // add args for time to die/eat/sleep
{
	int		i;
	t_vars	*vars;

	i = 0;
	vars = malloc(num_philo * sizeof(*vars) + 1000);
	if (!vars)
		return (NULL);
	while (i < num_philo)
	{
		(vars[i]).forks = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&(vars[i]).forks[i], NULL);
		(vars[i]).count_philo = num_philo;
		(vars[i]).time_to_die = 300;
		(vars[i]).time_to_eat = 10;
		(vars[i]).time_to_sleep = 50;
		(vars[i]).philo = malloc(sizeof(t_philo));
		(vars[i]).philo->id = i + 1;
		i++;
	}
	return (vars);
}


void	*philosopher_dines(void *arg) // probably philo id as argument; also needs info about time to eat etc.
{
	t_vars *vars = (t_vars *)arg;
	int	left;
	int	right;

	left = vars->philo->id - 1;
	if (vars->philo->id == vars->count_philo)
		right = 0;
	else
		right = vars->philo->id;
	while (1) // also stop if all philos have eaten at least x times (provided as argument)
	{
		if (vars->philo->id % 2 != 0)
		{
			// check if fork is logged, if not, take the left fork
			pthread_mutex_lock(&(vars->forks[left]));
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), vars->philo->id, left);
			usleep(5000000);
			pthread_mutex_unlock(&(vars->forks[left]));

			// check if fork is logged, if not, take the right fork
			pthread_mutex_lock(&(vars->forks[right]));
			printf("%d: Philosopher %d has taken taken fork %d\n", get_timestamp(), vars->philo->id, right);
			pthread_mutex_unlock(&(vars->forks[right]));
		}
		else if (vars->philo->id % 2 == 0)
		{
			// check if fork is logged, if not, take the right fork
			pthread_mutex_lock(&(vars->forks[right]));
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), vars->philo->id, right);
			pthread_mutex_unlock(&(vars->forks[right]));
			
			// check if fork is logged, if not, take the left fork
			pthread_mutex_lock(&(vars->forks[left]));
			printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), vars->philo->id, left);
			pthread_mutex_unlock(&(vars->forks[left]));
		}
		// if philo has two forks taken up, philo eats for X milliseconds (provided as argument); use usleep?
		printf("%d: Philosopher %d is eating\n", get_timestamp(), vars->philo->id);
		usleep(5000000); // takes microseconds 1000000ms = 1sec

		// once philo has finished eating, unlock the used forks

		//start sleeping for X milliseconds (provided as argument); use usleep?
		printf("%d: Philosopher %d is sleeping\n", get_timestamp(), vars->philo->id);
		usleep(5000000);

		printf("%d: Philosopher %d is thinking\n", get_timestamp(), vars->philo->id);
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
	while (i < num_philo)
	{
		// create threads for each philosopher (number is given by argv[1]; struct for each philo?)
		if (pthread_create(&newthread[i], NULL, philosopher_dines, &vars[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(newthread[i], NULL))
			return (1);
		pthread_mutex_destroy(&(vars[i]).forks[i]);
		i++;
	}
}