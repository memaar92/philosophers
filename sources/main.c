/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/29 17:23:16 by mamesser         ###   ########.fr       */
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

int	take_fork_even_philo(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, right);
	
	pthread_mutex_lock(philo->left_fork);
	printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, left);
	return (0);
}


int	take_fork_uneven_philo(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, left);
	usleep(5000000); // for testing purposes

	pthread_mutex_lock(philo->right_fork);
	printf("%d: Philosopher %d has taken fork %d\n", get_timestamp(), philo->id, right);
	return (0);
}

void	*philosopher_dines(void *arg) // probably philo id as argument; also needs info about time to eat etc.
{
	t_philo *philo = (t_philo *)arg;
	// definition of left and right for testing purposes
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
			take_fork_uneven_philo(philo, left, right);
		else if (philo->id % 2 == 0)
			take_fork_even_philo(philo, left, right);
		// if philo has two forks taken up, philo eats for X milliseconds (provided as argument);
		printf("%d: Philosopher %d is eating\n", get_timestamp(), philo->id);
		usleep(1000000); // takes microseconds 1000000ms = 1sec
		
		// once philo has finished eating, unlock the used forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		//start sleeping for X milliseconds (provided as argument);
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

	(void)(argc);
	(void)(argv);
	i = 0;
	newthread = malloc(num_philo * sizeof(*newthread));
	if (!newthread)
		return (1);
	vars = init_structs(num_philo);
	if (!vars)
		return (1);
	
	while (i < num_philo)
	{
		// create threads for each philosopher (number is given by argv[1]; struct for each philo?)
		if (pthread_create(&newthread[i], NULL, philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	// wait for threads to finish
	while (i < num_philo)
	{
		if (pthread_join(newthread[i], NULL))
			return (1);
		pthread_mutex_destroy(&(vars->forks[i]));
		i++;
	}
}