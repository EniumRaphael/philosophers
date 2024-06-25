/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:08:23 by rparodi           #+#    #+#             */
/*   Updated: 2024/06/17 12:24:16 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/_types/_null.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// printf derriere un mutex pour le printf
// zero printf apres une mort
// mort shared avec un mutex
// compte le nombre de ois manger par philo, et chec via un thread si tous a manger X fois

pthread_t philosopher[15];
pthread_mutex_t chopstick[15];

int	ft_sleep(size_t milliseconds)
{
	struct timeval start;
	struct timeval tempo;
	
	gettimeofday(&tempo, NULL);
	gettimeofday(&start, NULL);
	while ((tempo - start) < milliseconds)
	{
		usleep(500);
		gettimeofday(&tempo, NULL);
	}
	return (0);
}

void *func(void *arg) {
	int n = *((int *)arg);
	printf("Philosopher %d is thinking\n", n);

	pthread_mutex_lock(&chopstick[n]);
	pthread_mutex_lock(&chopstick[(n + 1) % 15]);
	printf("Philosopher %d is eating\n", n);
	ft_sleep(3000000); // sleep for 3 seconds to simulate eating
	pthread_mutex_unlock(&chopstick[n]);
	pthread_mutex_unlock(&chopstick[(n + 1) % 15]);
	printf("Philosopher %d finished eating\n", n);

	free(arg); // Free the allocated memory
	return NULL;
}

int main() {
	int i;

	for (i = 0; i < 15; i++)
		pthread_mutex_init(&chopstick[i], NULL);

	for (i = 0; i < 15; i++) {
		int *arg = malloc(sizeof(*arg));
		if (arg == NULL) {
			fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
			exit(EXIT_FAILURE);
		}
		*arg = i;
		pthread_create(&philosopher[i], NULL, func, arg);
	}

	for (i = 0; i < 15; i++)
		pthread_join(philosopher[i], NULL);

	for (i = 0; i < 15; i++)
		pthread_mutex_destroy(&chopstick[i]);

	return 0;
}

