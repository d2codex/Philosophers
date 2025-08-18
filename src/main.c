/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/18 17:39:12 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/**
 * @brief Initializes and starts the philosopher simulation.
 *
 * Sets synchronized start times, spawns philosopher threads,
 * and launches the monitor thread.
 *
 * @param args Simulation arguments and shared data.
 */
void	start_simulation(t_args *args)
{
	long	t_start;
	int	i;

	if (!args || !args->num_philos)
		return;
	t_start = get_time_ms() + 50;
	i = 0;
	while (i < args->num_philos)
	{
		args->philos[i].t_start = t_start;
		args->philos[i].t_last_meal_start = t_start;
		i++;
	}
	i = 0;
	while (i < args->num_philos)
	{
		pthread_create(&args->philos[i].thread, NULL,
			(void *)philo_routine, &args->philos[i]);
		i++;
	}
	pthread_create(&args->monitor_thread, NULL, monitor, args);
}

/**
 * @brief Stops the simulation and cleans up all resources.
 *
 * This function signals that the simulation has ended, waits for all
 * philosopher threads and the monitor thread to finish, destroys all
 * mutexes associated with forks, and frees dynamically allocated memory.
 *
 * @param args Pointer to the t_args struct containing simulation data.
 * @param forks Pointer to the array of fork mutexes to destroy and free.
 */
void	stop_simulation(t_args *args, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < args->num_philos)
	{
		pthread_join(args->philos[i].thread, NULL);
		i++;
	}
	pthread_join(args->monitor_thread, NULL);
	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(args->philos);
	free(forks);
}

int	main(int ac, char **av)
{
	t_args	args;
	pthread_mutex_t	*forks;

	forks = NULL;
	if (parse_init_args(ac, av, &args) != 0)
		return (print_usage(), 1);
	if (validate_args(ac, &args) != 0)
		return (print_usage(), 1);
	if (args.num_philos == 1)
	{
		handle_one_philo(&args);
		return (1);
	}
	if (pthread_mutex_init(&args.print_lock, NULL) != 0)
		return (cleanup(&args, NULL, "init print mutex failed"), 1);
	if (init_forks(&forks, args.num_philos) != 0)
		return (cleanup(&args, NULL, "init forks failed"), 1);
	if (init_philos(&args.philos, &args, forks) != 0)
		return (cleanup(&args, forks, "init philos failed"),1);
	start_simulation(&args);
	stop_simulation(&args, forks);
	return (0);
}
