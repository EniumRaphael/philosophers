/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:30:25 by rparodi           #+#    #+#             */
/*   Updated: 2024/07/18 21:07:01 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	t_thread	watch_dogs;
	t_usize		i;

	i = 0;
	if (pthread_create(&watch_dogs, NULL, &ft_watch_dogs, prog->philos))
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
	while (i-- > 0)
		pthread_join(prog->philos[i].thread, NULL);
	pthread_join(watch_dogs, NULL);
	return (NO_ERROR);
}

t_usize	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_exit("Error of during ft_time !\n", 1);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

t_i32	main(t_i32 argc, t_str *argv)
{
	t_philo		philo[MAXSUPPORT];
	t_program	prog;
	t_i32		i;
	t_i32		j;

	j = 1;
	if (argc != 6 && argc != 5)
		ft_exit(ARGS, 1);
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] != '\0')
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				ft_exit("I have to take only numeric arguments !\n", 1);
			i++;
		}
		j++;
	}
	if (ft_atou_return(argv[1]) > MAXSUPPORT)
		ft_exit("Please update the max support !\n", 1);
	if (ft_init(argc, argv, &prog, philo))
		ft_exit("Issues during initialisation\n", ERROR);
	return (0);
}
