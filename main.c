/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/27 18:20:28 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	*philosopher_dines(void *arg) // probably philo id as argument; also needs info about time to eat etc.
{
	t_vars *vars = (t_vars *)arg;
	
	printf("philo id: %d\n", vars->philo->id);
	
	// while (1) // also stop if all philos have eaten at least times (provided as argument)
	// {
	// 	// if philo id is odd, take up right fork first
	// 	// check if fork is logged, if not, take the fork
	// 	printf("TIMESTAMP: Philosopher %d has taken a fork\n", philo_id);
		
	// 	// if philo id is even, take up left fork first
	// 	// check if fork is logged, if not, take the fork

	// 	// if philo has two forks taken up, philo eats for X milliseconds (provided as argument); use usleep?
	// 	printf("TIMESTAMP: Philosopher %d is eating\n", philo_id);

	// 	// once philo has finished eating, unlock the used forks

	// 	//start sleeping for X milliseconds (provided as argument); use usleep?
	// 	printf("TIMESTAMP: Philosopher %d is sleeping\n", philo_id);

	// 	printf("TIMESTAMP: Philosopher %d is thinking\n", philo_id);
	// }
	return (NULL);
}


int	main(int argc, char **argv)
{
	pthread_t	newthread[10]; // array of threads needs to be dynamic (bc dependent on input)
	t_vars		vars;
	int			i;

	i = 1;
	vars.time_to_die = 300;
	vars.time_to_eat = 10;
	vars.time_to_sleep = 50;
	while (i < 10)
	{
		vars.philo->id = i;
		// create threads for each philosopher (number is given by argv[1]; struct for each philo?)
		if (pthread_create(&newthread[i], NULL, philosopher_dines, &vars))
			return (1);
		i++;
	}
	i = 1;
	while (i < 10)
	{
		if (pthread_join(newthread[i], NULL))
			return (1);
	}
}