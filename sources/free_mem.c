/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:11:49 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/04 13:30:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_mem(t_vars *vars, pthread_t *newthread, pthread_t *checking)
{
	if (vars && vars->forks)
		free(vars->forks);
	if (vars && vars->philo)
		free(vars->philo);
	if (vars)
		free(vars);
	if (newthread)
		free(newthread);
	if (checking)
		free(checking);
}