/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/17 21:57:29 by diade-so         ###   ########.fr       */
=======
/*   Updated: 2025/08/18 15:16:32 by diade-so         ###   ########.fr       */
>>>>>>> 9f157d6 (Refactor timing and fork acquisition logic)
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
	if (args.num_philos == 1)
	{
		handle_one_philo(&args);
		return (1);
	}
	if (pthread_mutex_init(&args.print_lock, NULL) != 0)
		return (1);
	if (init_forks(&forks, args.num_philos) != 0)
		return (1);
	if (init_philos(&args.philos, &args, forks) != 0)
		return (1);
	start_simulation(&args);
<<<<<<< HEAD
	// end simulation
	// 	-death detected or meal_goal reached
	// 	-join threads
	// 	-destroy mutexes
	// 	-free all allocated memory
=======
>>>>>>> 9f157d6 (Refactor timing and fork acquisition logic)
	return (0);
}

