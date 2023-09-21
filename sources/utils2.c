/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:13:21 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/21 10:41:59 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	num_len(int i)
{
	int	len;

	len = 0;
	while (i > 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}

int	check_size(char **argv)
{
	if (ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10
		|| ft_strlen(argv[3]) > 10 || ft_strlen(argv[4]) > 10)
		return (1);
	if (ft_strlen(argv[1]) != num_len(ft_atoi(argv[1]))
		|| ft_strlen(argv[2]) != num_len(ft_atoi(argv[2]))
		|| ft_strlen(argv[3]) != num_len(ft_atoi(argv[3]))
		|| ft_strlen(argv[4]) != num_len(ft_atoi(argv[4])))
		return (1);
	return (0);
}
