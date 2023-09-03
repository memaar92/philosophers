/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:58:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/03 18:33:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	pthread_t	*checking;
	t_vars		*vars;
	int			i;

	if (argc < 5)
		return (printf("Please provide at least 4 arguments.\n"), 1);
	i = 0;
	if (init_vars(&checking, &newthread, argv, &vars))
		return (1);
	if (create_threads(checking, newthread, vars, argc))
		return (1);
	while (i < vars->num_philo)
	{
		if (pthread_join(newthread[i], NULL))
			return (1);
		pthread_mutex_destroy(&(vars->forks[i]));
		i++;
	}
}

/*
TODOS:
- there are still issues with larger numbers of philos (e.g. 40 800 200 200  & 20 800 200 200); may wait in case of uneven philos at the beginning
- number of meals eaten does not start at 0 --> problem?
- mutex for ensuring that philo does not start eating and dies at the same time
- check for data races
- free mem and check for leaks
*/

