/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:34:23 by diade-so          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/17 21:59:21 by diade-so         ###   ########.fr       */
=======
/*   Updated: 2025/08/18 15:22:46 by diade-so         ###   ########.fr       */
>>>>>>> 9f157d6 (Refactor timing and fork acquisition logic)
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Initializes an array of mutexes representing forks.
 *
 * Allocates memory for `num_philos` mutexes and initializes each one in
 * the unlocked state. If allocation or initialization fails, previously
 * initialized mutexes are destroyed and memory is freed.
 *
 * @param forks Pointer to the array of mutexes to allocate and initialize.
 * @param num_philos Number of mutexes (forks) to create.
 *
 * @return 0 on success, 1 on failure.
 */
int	init_forks(pthread_mutex_t **forks, int num_philos)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!*forks)
		return (error_return("Failed to malloc for forks\n"));
	i = 0;
	while (i < num_philos)
	{
		if(pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			while (--i >=0)
				pthread_mutex_destroy(&(*forks)[i]);
			free(*forks);
			*forks = NULL;
			return (error_return("Mutex init failed\n"));
		}
		i++;
	}
	return (0);
}

/**
 * @brief Initializes philosopher array and assigns forks.
 *
 * Allocates and sets up each philosopher with an ID, shared args,
 * pointers to fork1 and fork2, initial state, and timestamps.
 *
 * @param philos Pointer to philosopher array to allocate and initialize.
 * @param args Shared arguments/configuration.
 * @param forks Array of mutex forks to assign to philosophers.
 *
 * @return 0 on success, 1 on failure.
 */
int	init_philos(t_philo **philos, t_args *args, pthread_mutex_t *forks)
{
	int	i;
	int	count;
	
	count = args->num_philos;
	*philos = malloc(sizeof(t_philo) * count);
	if (!*philos)
		return (error_return("Failed to malloc for philos\n"));
	i = 0;
	while (i < count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].args = args;
		(*philos)[i].fork1 = &forks[i];
		(*philos)[i].fork2 = &forks[(i + 1) % count];
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].t_last_meal_start = 0;
		(*philos)[i].state = THINKING;
		i++;
	}
	return (0);
}

/**
 * @brief Handles the single-philosopher edge case.
 *
 * In a simulation with only one philosopher, the philosopher cannot eat
 * because there is only one fork. This function prints the appropriate
 * messages for taking the fork and dying after time_til_death milliseconds.
 *
 * @param args Pointer to the simulation arguments structure (t_args).
 */
void	handle_one_philo(t_args *args)
{
	long	start;
	long	elapsed;

	start = get_time_ms();
	elapsed = get_time_ms() - start;
	printf("%ld 1 has taken a fork\n", elapsed);
	usleep(args->time_til_death * 1000);
	printf("%ld 1 died\n", elapsed + args->time_til_death);
}
