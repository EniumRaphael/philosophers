/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:42:31 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/20 15:04:13 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_check == true)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

t_bool	check_dead(t_philo *philo)
{
	t_usize	i;

	i = 0;
	while (i < philo[0].nb_philo)
	{
		if (ft_time() - philo[i].t_last_eat > philo[i].t_eat)
			return (true);
	}
	i++;
	return (false);
}

t_bool	check_eat(t_philo *philo)
{
	t_usize	i;
	t_u8	check;

	i = 0;
	check = 0;
	if (philo[0].nb_eat == -1)
		return (false);
	while (i < philo[0].nb_philo)
	{
		if (philo[i].eating_count >= philo[i].nb_eat)
			check++;
		i++;
	}
	if (check == philo[0].nb_philo)
		return (true);
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
		if (check_dead(philo))
			break ;
		if (check_eat(philo))
			break ;
	}
	return (philo);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo == NULL)
		return (NULL);
	while (!dead_loop(philo))
	{
		ft_start_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (philo);
}

t_error	ft_init_thread(t_program *prog, t_mutex *forks)
{
	t_thread	o_block;
	t_usize		i;

	i = 0;
	if (pthread_create(&o_block, NULL, &ft_watch_dogs, prog->philos))
		ft_destroy_exit("Allocation of watch_dogs failed\n", \
			ERROR, prog, forks);
	while (i < prog->philos[0].nb_philo)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, &ft_routine, \
					&prog->philos[i]))
			ft_destroy_exit("Allocation of one philo thread failed !\n", \
					ERROR, prog, forks);
		i++;
	}
	pthread_join(o_block, NULL);
	while (--i > 0)
		pthread_join(prog->philos[i].thread, NULL);
	return (NO_ERROR);
}
