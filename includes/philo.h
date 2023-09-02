/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:12:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/02 15:55:26 by mamesser         ###   ########.fr       */
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

typedef struct s_vars	t_vars;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				count_philo;
	int				start_eat; //instead using calculated death time
	long			time_of_death;
	int				meals_eaten;
	t_vars			*vars;
}				t_philo;


typedef struct s_vars
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				all_alive;
	long			start_sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}				t_vars;

t_vars *init_structs(char **argv, int num_philo);
int		ft_atoi(const char *str);

#endif