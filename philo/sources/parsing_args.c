/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:42:37 by rparodi           #+#    #+#             */
/*   Updated: 2024/07/24 20:23:09 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

t_error	ft_parsing_args(t_i32 argc, t_str *argv, t_philo *philo)
{
	t_usize	tmp;

	tmp = 0;
	philo->eating = 0;
	philo->eating_count = 0;
	ft_atou(argv[1], &tmp);
	if (tmp == 0)
		return (ERROR);
	philo->nb_philo = tmp;
	philo->nb_eat = ~0u;
	if (argc == 6)
	{
		ft_atou(argv[5], &tmp);
		if (tmp == 0)
			return (ERROR);
		philo->nb_eat = tmp;
	}
	ft_atou(argv[2], &tmp);
	philo->t_death = tmp;
	ft_atou(argv[3], &tmp);
	philo->t_eat = tmp;
	ft_atou(argv[4], &tmp);
	philo->t_sleep = tmp;
	return (NO_ERROR);
}

t_error	ft_init_fork(t_mutex *fork, t_usize nb_fork)
{
	t_usize	i;

	i = 0;
	while (i < nb_fork)
	{
		fork[i] = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	return (NO_ERROR);
}

void	ft_pause(size_t milliseconds)
{
	const t_usize	start = ft_time();

	while ((ft_time() - start) < milliseconds)
		usleep(500);
}

t_error	ft_init_philo(t_i32 argc, t_str *argv, t_program *prog, t_mutex *forks)
{
	t_usize	i;
	t_usize	start_time;

	start_time = ft_time() + 500;
	i = 0;
	while (i < ft_atou_return(argv[1]))
	{
		prog->philos[i].id = i + 1;
		ft_parsing_args(argc, argv, &prog->philos[i]);
		prog->philos[i].start_time = start_time;
		prog->philos[i].t_last_eat = 0;
		prog->philos[i].print_lock = &prog->print_lock;
		prog->philos[i].dead_lock = &prog->dead_lock;
		prog->philos[i].meal_lock = &prog->meal_lock;
		prog->philos[i].dead_check = false;
		prog->philos[i].check_eating_count = &prog->check_eating_count;
		if (i == 0)
			prog->philos[i].r_fork = &forks[prog->philos[i].nb_philo - 1];
		else
			prog->philos[i].r_fork = &forks[i - 1];
		prog->philos[i].l_fork = &forks[i];
		i++;
	}
	return (ft_parsing_args(argc, argv, prog->philos));
}

t_error	ft_init(t_i32 argc, t_str *argv, t_program *prog, t_philo *philo)
{
	static t_mutex	forks[MAXSUPPORT] = {0};

	prog->print_lock = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
	prog->dead_lock = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
	prog->meal_lock = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
	prog->check_eating_count = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
	prog->philos = philo;
	prog->dead_flag = false;
	ft_init_fork(forks, ft_atou_return(argv[1]));
	if (ft_init_philo(argc, argv, prog, forks))
		return (ERROR);
	if (philo->nb_philo != 0 && philo->nb_philo > MAXSUPPORT)
		return (ERROR);
	ft_init_thread(prog, forks);
	return (NO_ERROR);
}
