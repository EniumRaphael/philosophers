/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:42:31 by rparodi           #+#    #+#             */
/*   Updated: 2024/07/04 13:29:39 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo[0].dead_check == true)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

t_bool	check_dead(t_philo *philo)
{
	t_usize	i;
	t_usize	timecheck;

	i = 0;
	while (i < philo[0].nb_philo)
	{
		timecheck = ft_time() - philo[i].start_time - philo[i].t_last_eat;
		if (philo[i].t_last_eat != 0 && timecheck >= philo[i].t_death)
		{
			pthread_mutex_unlock(philo[i].dead_lock);
			ft_logs("died\n", &philo[i]);
			philo[i].dead_check = true;
			pthread_mutex_lock(philo[i].dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

void	counting_launch(t_philo *philo, t_u8 *counter)
{
	t_usize	i;

	i = 0;
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[i].check_eating_count);
		if (philo[i].eating_count >= philo[i].nb_eat)
			(*counter)++;
		pthread_mutex_unlock(philo[i].check_eating_count);
		i++;
	}
}

t_bool	check_eat(t_philo *philo)
{
	t_usize	i;
	t_u8	check;

	i = 0;
	check = 0;
	if (philo[0].nb_eat == -1)
		return (false);
	counting_launch(philo, &check);
	if (check == philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		while (i < philo[0].nb_philo)
		{
			pthread_mutex_unlock(philo[i].dead_lock);
			philo[i].dead_check = true;
			pthread_mutex_lock(philo[i].dead_lock);
			i++;
		}
		pthread_mutex_unlock(philo[0].dead_lock);
		return (true);
	}
	return (false);
}

void	*ft_watch_dogs(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo == NULL)
		return (NULL);
	while (true)
	{
		if (check_eat(philo) == true)
			break ;
		if (check_dead(philo) == true)
			break ;
	}
	return (philo);
}
