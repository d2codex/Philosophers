/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/13 16:06:45 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	t_args	args;
	pthread_mutex_t	*forks;
	t_philo		*philos;

	forks = NULL;
	philos = NULL;
	if (parse_init_args(ac, av, &args) != 0)
		return (print_usage(), 1);
	if (validate_args(&args) != 0)
		return (print_usage(), 1);
	if (pthread_mutex_init(&args.print_lock, NULL) != 0)
		return (1);
	if (init_forks(&forks, args.philos) != 0)
		return (1); // destroy print_mutex
	if (init_philos(&philos, &args, forks) != 0)
		return (1); // destory print/fork mutex & free fork array
	// start simulation
	// 	- use helper function to delay start time so threads can sync up
	// 	- loop to create the threads (one per philo)
	// 		-routine function / add delay function here for sync
	// 			-separate functions for each action?
	// 			-actions need to be printed with timestamp
	// 				-set state to print action
	// 			-need mutex for printing to prevent data race
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

