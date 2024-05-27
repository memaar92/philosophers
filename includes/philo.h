/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:12:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/21 10:39:22 by mamesser         ###   ########.fr       */
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
	long			time_of_death;
	int				meals_eaten;
	t_vars			*vars;
}				t_philo;

typedef struct s_vars
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_philo;
	int				all_alive;
	int				all_full;
	int				num_meals;
	pthread_mutex_t	flag;
	long			start_sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*alive;
}				t_vars;

int		ft_atoi(const char *str);
int		check_args(int argc, char **argv);
int		print_msg(char *str, t_philo *philo);

long	get_time(void);
int		ft_usleep(int wait);

int		take_forks(t_philo *philo);
int		increment_num_meals(t_philo *philo);
int		eat(t_philo *philo);
int		ft_sleep(t_philo *philo);

int		init_vars(pthread_t **checking, pthread_t **newthread,
			char **argv, t_vars **vars);
t_vars	*init_structs(char **argv, int num_philo);
int		init_philos(t_vars *vars, int num_philo);
int		set_static_vars(t_vars *vars, char **argv, int num_philo);
t_vars	*alloc_mem(int num_philo);

int		create_threads(pthread_t *checking, pthread_t *newthread, t_vars *vars);
void	*check_on_philos(void *arg);
int		check_death(t_vars *vars, int i);
void	init_time_of_death(t_philo *philo);
void	*philosopher_dines(void *arg);

void	free_mem(t_vars *vars, pthread_t *newthread, pthread_t *checking);

int		ft_strlen(const char *s);
int		num_len(int i);
int		check_size(char **argv);

#endif