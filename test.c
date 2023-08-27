/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:30:26 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/27 17:41:56 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

// dining philo problem

// use helgrind to check for data races

// create a thread for each philo (number of philos are given in args)

// init forks based on the number of philos

// protect the forks' state with mutexes (one mutex for each fork)

// What if there is only one philo? How can they eat as there is only one fork?

// track last meal of a specific philo and simulation start?

// (x / 2) philos can eat at the same time

void	*test1(void *arg)
{
	int	i;
	
	i = -1;
	while(++i < 10)
	{
		sleep(1);
		printf("Hey\n");
	}
	return (NULL);
}

void	test2(void)
{
	int	i;
	
	i = -1;
	while(++i < 2)
	{
		sleep(2);
		printf("ya\n");
	}
}


int	main(void)
{
	pthread_t	newthread;

	if (pthread_create(&newthread, NULL, test1, NULL))
		return (1); // starts a new thread with test1 as the start_routine; arg of test1 is set to NULL
	test2();
	if (pthread_join(newthread, NULL))
		return (1); // will wait for a specific thread (in this case newthread, in which test1 runs); the second arguments gets the return value from the thread_function
}

// concurrency vs. parallelism

// A mutex (mutual exclusion) is a variable type that represents something like a "locked door" / lock around a section of code