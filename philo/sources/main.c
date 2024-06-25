/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:30:25 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/16 12:22:40 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_i32	main(t_i32 argc, t_str *argv)
{
	t_philo		philo[MAXSUPPORT];
	t_program	prog;

	if (argc != 6 && argc != 5)
		ft_exit(ARGS, 1);
	if (ft_init(argc, argv, &prog, philo))
		ft_exit("Issues during initialisation\n", ERROR);
	return (0);
}
