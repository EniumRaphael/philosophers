/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:42:37 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/18 15:09:06 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_error	ft_parsing_args(t_i32 argc, t_str *argv, t_philo *philo)
{
	t_usize	tmp;

	tmp = 0;
	if (argc == 6)
	{
		ft_atou(argv[5], &tmp);
		philo->nb_eat = tmp;
	}
	else
		philo->t_eat = -1;
	ft_atou(argv[1], &tmp);
	philo->nb_philo = tmp;
	ft_atou(argv[2], &tmp);
	philo->t_death = tmp;
	ft_atou(argv[3], &tmp);
	philo->t_eat = tmp;
	ft_atou(argv[4], &tmp);
	philo->t_sleep = tmp;
	return (NO_ERROR);
}

t_error	ft_init_fork(t_philo *philo, t_mutex *fork)
{
	t_usize	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (NO_ERROR);
}

t_usize	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_exit("Error of during ft_time !\n", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

	i = 0;
	while (i < ft_atou_return(argv[1]))
	{
		prog->philos[i].id = i + 1;
		prog->philos[i].eating = 0;
		ft_parsing_args(argc, argv, &prog->philos[i]);
		prog->philos[i].start_time = ft_time();
		prog->philos[i].t_last_eat = ft_time();
		prog->philos[i].print_lock = &prog->print_lock;
		prog->philos[i].dead_lock = &prog->dead_lock;
		prog->philos[i].meal_lock = &prog->meal_lock;
		prog->philos[i].dead_check = &prog->dead_flag;
		prog->philos[i].l_fork = &forks[i];
		if (i == 0)
			prog->philos[i].r_fork = &forks[prog->philos[i].nb_philo - 1];
		else
			prog->philos[i].r_fork = &forks[i - 1];
		i++;
	}
	if (ft_parsing_args(argc, argv, prog->philos))
		return (ERROR);
	return (NO_ERROR);
}

t_error	ft_init(t_i32 argc, t_str *argv, t_program *prog, t_philo *philo)
{
	static t_mutex	forks[MAXSUPPORT] = { 0 };

	pthread_mutex_init(&prog->print_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	prog->philos = philo;
	prog->dead_flag = 0;
	if (ft_init_philo(argc, argv, prog, forks))
		return (ERROR);
	if (philo->nb_philo != 0 && philo->nb_philo > MAXSUPPORT)
		return (ERROR);
	ft_init_thread(prog, forks);
	return (NO_ERROR);
}
