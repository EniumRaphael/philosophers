/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:23:50 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/17 12:38:01 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_usize	ft_strlen(t_str str)
{
	t_usize	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(t_i32 fd, t_str str)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_exit(t_str msg, t_u8 status)
{
	ft_putchar_fd(status + 1, msg);
	exit(status);
}

void	ft_destroy_exit(t_str msg, t_u8 status, t_program *prog, t_mutex *forks)
{
	t_usize	i;

	i = 0;
	pthread_mutex_destroy(&prog->print_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	while (i < prog->philos[0].nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	ft_exit(msg, status);
}
