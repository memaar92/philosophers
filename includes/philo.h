/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:12:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/04 17:09:12 by mamesser         ###   ########.fr       */
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
	long			time_of_death;
	int				meals_eaten;
	t_vars			*vars;
}				t_philo;

typedef struct s_vars
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo;
	int				all_alive;
	int				all_full;
	int				num_meals;
	long			start_sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*alive;
}				t_vars;

int		ft_atoi(const char *str);

long	get_timestamp(t_philo *philo);
long	calc_start_time(void);
int		ft_usleep(int wait);

int		take_fork_even_philo(t_philo *philo);
int		take_fork_uneven_philo(t_philo *philo);
int		take_forks(t_philo *philo);
int		eat(t_philo *philo);
int		ft_sleep(t_philo *philo);

int		init_vars(pthread_t **checking, pthread_t **newthread, 
			char **argv, t_vars **vars);
t_vars	*init_structs(char **argv, int num_philo);
int		init_philos(t_vars *vars, int num_philo);
void	set_static_vars(t_vars *vars, char **argv, int num_philo);
t_vars	*alloc_mem(int num_philo);

int		create_threads(pthread_t *checking, pthread_t *newthread, t_vars *vars, int argc);
void	*check_on_philos(void *arg);
void	*check_philos_full(void *arg);
void	*philosopher_dines(void *arg);

void	free_mem(t_vars *vars, pthread_t *newthread, pthread_t *checking);

#endif