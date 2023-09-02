/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/02 16:39:06 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long get_timestamp(t_philo *philo) // 1000 microsec are 1 millisec
{
	struct timeval	tv;
	long			time;
	
	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000) - philo->vars->start_sim;
	return(time);
}

long	calc_start_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec) / 1000;
	return (time);
}

int	take_fork_even_philo(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->right_fork);
	if (!(philo->vars->all_alive))
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, right);
	
	pthread_mutex_lock(philo->left_fork);
	if (!(philo->vars->all_alive))
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, left);
	return (0);
}

void *check_on_philos(void *arg)
{
	t_vars *vars = (t_vars *)arg;
	struct timeval	tv;
	int				i;
	int				j;
	int				num_philos;

	num_philos = vars->philo[0].count_philo;
	j = 0;
	while(vars->all_alive)
	{
		i = 0;
		while (i < num_philos)
		{
			gettimeofday(&tv, NULL);
			if (vars->philo[i].time_of_death <= (tv.tv_sec * 1000000 + tv.tv_usec))
			{
				vars->all_alive = 0;
				printf("%ld: Philosopher %d died\n", get_timestamp(vars->philo), vars->philo[i].id);
				while (j < num_philos)
					pthread_mutex_unlock(&vars->forks[j++]);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}


int	take_fork_uneven_philo(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->left_fork);
	if (!(philo->vars->all_alive))
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, left);
	// usleep(50000); // for testing purposes

	pthread_mutex_lock(philo->right_fork);
	if (!(philo->vars->all_alive))
		return (1);
	printf("%ld: Philosopher %d has taken fork %d\n", get_timestamp(philo), philo->id, right);
	return (0);
}

void	*philosopher_dines(void *arg) // probably philo id as argument; also needs info about time to eat etc.
{
	t_philo *philo = (t_philo *)arg;
	struct timeval	tv;
	// definition of left and right for testing purposes
	int	left;
	int	right;

	left = philo->id - 1;
	if (philo->id == philo->count_philo)
		right = 0;
	else
		right = philo->id;
	while (philo->vars->all_alive) // also stop if all philos have eaten at least x times (provided as argument)
	{
		if (philo->id % 2 != 0)
			take_fork_uneven_philo(philo, left, right);
		else if (philo->id % 2 == 0)
			take_fork_even_philo(philo, left, right);
		// if philo has two forks taken up, philo eats for X milliseconds (provided as argument);
		if (!(philo->vars->all_alive))
			return (NULL);
		printf("%ld: Philosopher %d is eating\n", get_timestamp(philo), philo->id);
		gettimeofday(&tv, NULL);
		philo->time_of_death = tv.tv_sec * 1000000 + tv.tv_usec + (philo->vars->time_to_die * 1000);
		ft_usleep(philo->vars->time_to_eat * 1000);
		// track the point in time the philo has started eating and store it in the respective philo struct
		// track the number of meals a philo has consumed
		
		// once philo has finished eating, unlock the used forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		//start sleeping for X milliseconds (provided as argument);
		if (!(philo->vars->all_alive))
			return (NULL);
		printf("%ld: Philosopher %d is sleeping\n", get_timestamp(philo), philo->id);
		ft_usleep(philo->vars->time_to_sleep * 1000);

		printf("%ld: Philosopher %d is thinking\n", get_timestamp(philo), philo->id);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	pthread_t	checking;
	t_vars		*vars;
	int			num_philo;
	int			i;

	if (argc < 5)
		return (printf("Too few arguments\n"), 1);
	i = 0;
	num_philo = ft_atoi(argv[1]);
	checking = malloc(sizeof(*checking));
	if (!checking)
		return (1);
	newthread = malloc(num_philo * sizeof(*newthread));
	if (!newthread)
		return (1);
	vars = init_structs(argv, num_philo);
	if (!vars)
		return (1);
	if (pthread_create(&checking, NULL, check_on_philos, vars))
		return (1);
	vars->start_sim = calc_start_time();
	while (i < num_philo)
	{
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

/*
TODOS:
- timestamp should probably start at 0?
- How to account for the inaccuracy of the usleep function?

*/

