/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:23:09 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/18 15:50:49 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_logs(t_str msg, t_philo *philo)
{
	const t_usize	time = ft_time() - philo->start_time;

	if (msg != NULL)
		printf("%s%zu %s%i %s%s%s", BLUE, time, GOLD, philo->id, GREEN, msg, END);
}

t_error	ft_thinking(t_philo *philo)
{
	ft_logs("is thinking\n", philo);
	return (NO_ERROR);
}

t_error	ft_start_eating(t_philo *philo)
{
	const t_usize	time = ft_time() - philo->start_time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_logs("has taken a fork\n", philo);
		pthread_mutex_lock(philo->r_fork);
		ft_logs("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_logs("has taken a fork\n", philo);
		pthread_mutex_lock(philo->l_fork);
		ft_logs("has taken a fork\n", philo);
	}
	philo->eating = true;
	ft_logs("is eating\n", philo);
	philo->t_last_eat = time;
	philo->eating_count++;
	ft_pause(EATTIME * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eating = false;
	return (NO_ERROR);
}

t_error	ft_sleeping(t_philo *philo)
{
	ft_logs("is sleeping\n", philo);
	ft_pause(philo->t_sleep);
	return (NO_ERROR);
}
