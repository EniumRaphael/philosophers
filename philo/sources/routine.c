/* ************************************************************************** */
/*                                                                          */
/*                                                      :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:42:31 by rparodi           #+#    #+#             */
/*   Updated: 2024/07/18 21:18:49 by rparodi          ###   ########.fr       */
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
		pthread_mutex_lock(philo->meal_lock);
		timecheck = ft_time() - philo[i].start_time - philo[i].t_last_eat;
		if (timecheck >= philo[i].t_death)
		{
			pthread_mutex_unlock(philo->meal_lock);
			ft_logs("died\n", &philo[i]);
			pthread_mutex_lock(philo[i].dead_lock);
			philo[i].dead_check = true;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (true);
		}
		pthread_mutex_unlock(philo->meal_lock);
		i++;
	}
	return (false);
}

void	counting_launch(t_philo *philo, t_u8 *counter)
{
	t_usize	i;

	i = 0;
	if (philo->nb_eat == -1)
		return ;
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
	t_u8	check;

	check = 0;
	counting_launch(philo, &check);
	if (check == philo[0].nb_philo)
		return (true);
	return (false);
}

void	*ft_watch_dogs(void *ptr)
{
	t_philo	*philo;
	t_usize	i;

	philo = (t_philo *) ptr;
	if (philo == NULL)
		return (NULL);
	i = philo[0].nb_philo;
	while (true)
	{
		if (check_eat(philo) == true)
			break ;
		if (check_dead(philo) == true)
			break ;
	}
	while (i-- != 0)
	{
		pthread_mutex_lock(philo[i].dead_lock);
		philo[i].dead_check = true;
		pthread_mutex_unlock(philo[i].dead_lock);
	}
	return (philo);
}
