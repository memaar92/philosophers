/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:12:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/29 15:47:13 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				count_philo;
	// some timestamp to determine starvation
	
}				t_philo;


typedef struct s_vars
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}				t_vars;

t_vars *init_structs(int num_philo);

#endif