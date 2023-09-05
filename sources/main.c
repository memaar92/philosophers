/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/05 16:07:34 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	pthread_t	*checking;
	t_vars		*vars;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Please provide at least 4 arguments.\n"), 1);
	if (check_args(argc, argv))
		return (1);
	i = 0;
	if (init_vars(&checking, &newthread, argv, &vars))
		return (free_mem(vars, newthread, checking), 1);
	if (create_threads(checking, newthread, vars))
		return (free_mem(vars, newthread, checking), 1);
	while (i < vars->num_philo)
	{
		if (pthread_join(newthread[i], NULL))
			return (free_mem(vars, newthread, checking), 1);
		pthread_mutex_destroy(&(vars->forks[i])); // only destroys unlocked mutexes
		i++;
	}
	pthread_mutex_destroy(vars->alive);
	free_mem(vars, newthread, checking);
}

/*
TODOS:
- there are still issues with larger numbers of philos (200)
- check with helgrind
*/

