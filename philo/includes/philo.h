/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:34:04 by rparodi           #+#    #+#             */
/*   Updated: 2024/07/23 21:04:56 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>
# include <stdbool.h>
# include "./types.h"

# define ARGS "Usage: ./philo <nb_philo> <t_death> <t_eat> <t_sleep> (<nb_eat>)"

# define GREEN "\033[32m"
# define GREY "\033[0;90m"
# define RED "\033[0;31m"
# define BLUE "\033[34m"
# define GOLD "\033[38;5;220m"
# define END "\033[0m"

# ifndef MAXSUPPORT
#  define MAXSUPPORT 200
# endif

typedef struct s_philo
{
	t_usize		nb_philo;
	t_usize		t_eat;
	t_usize		t_death;
	t_usize		t_sleep;
	t_usize		nb_eat;
	pthread_t	thread;
	t_i32		id;
	t_i32		eating;
	t_usize		eating_count;
	t_usize		t_last_eat;
	t_usize		start_time;
	t_bool		dead_check;
	t_mutex		*check_eating_count;
	t_mutex		*r_fork;
	t_mutex		*l_fork;
	t_mutex		*print_lock;
	t_mutex		*dead_lock;
	t_mutex		*meal_lock;
}				t_philo;

typedef struct s_program
{
	t_i32	dead_flag;
	t_mutex	dead_lock;
	t_mutex	meal_lock;
	t_mutex	print_lock;
	t_mutex	check_eating_count;
	t_philo	*philos;
}			t_program;

t_usize	ft_time(void);
void	ft_free(void *ptr);
t_usize	ft_strlen(t_str str);
void	*ft_routine(void *ptr);
void	*ft_watch_dogs(void *ptr);
t_bool	dead_loop(t_philo *philo);
t_bool	check_eat(t_philo *philo);
t_usize	ft_atou_return(t_str str);
t_bool	check_dead(t_philo *philo);
t_error	ft_thinking(t_philo *philo);
t_error	ft_sleeping(t_philo *philo);
t_i32	main(t_i32 argc, t_str *argv);
void	ft_pause(size_t milliseconds);
void	ft_exit(t_str msg, t_u8 status);
t_error	ft_start_eating(t_philo *philo);
t_error	ft_ending_eating(t_philo *philo);
void	ft_putchar_fd(t_i32 fd, t_str str);
void	ft_logs(t_str msg, t_philo *philo);
t_error	ft_atou(const char *nptr, t_usize *value);
t_error	ft_init_fork(t_mutex *fork, t_usize nb_fork);
void	counting_launch(t_philo *philo, t_u8 *counter);
t_error	ft_init_thread(t_program *prog, t_mutex *forks);
t_error	ft_parsing_args(t_i32 argc, t_str *argv, t_philo *philo);
t_error	ft_init(t_i32 argc, t_str *argv, t_program *prog, t_philo *philo);
t_error	ft_init_philo(t_i32 argc, t_str *argv, t_program *prog, t_mutex *forks);
void	ft_destroy_exit(t_str msg, t_u8 status, t_program *prog, \
		t_mutex *forks);

#endif
