/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/17 12:13:24 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_t	monitor_thread;

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
	pthread_create(&monitor_thread, NULL, monitor, args);
	//eventually move to end_simulation() function
	i = 0;
	while (i < args->num_philos)
		pthread_join(args->philos[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
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
	if (pthread_mutex_init(&args.print_lock, NULL) != 0)
		return (1);
	if (init_forks(&forks, args.num_philos) != 0)
		return (1); // destroy print_mutex
	if (init_philos(&args.philos, &args, forks) != 0)
		return (1); // destory print/fork mutex & free fork array
	start_simulation(&args);
	// start simulation
	// 	- use helper function to delay start time so threads can sync up **DONE**
	// 	- loop to create the threads (one per philo)
	// 		-routine function / add delay function here for sync **DONE**
	// 			-separate functions for each action **DONE**
	// 			-actions need to be printed with timestamp **DONE**
	// 				-set state to print action **DONE**
	// 			-need mutex for printing to prevent data race **DONE**
	// 		-update t_start to sync up with delay time
	// 	- need monitor thread
	// 		-here it routinely checks status specfically for
	// 		-time last eaten and if meal goals reached.
	// 		-need to also sync delay time here too
	// end simulation
	// 	-death detected or meal_goal reached
	// 	-join threads
	// 	-destroy mutexes
	// 	-free all allocated memory
	return (0);
}

