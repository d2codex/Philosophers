/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/17 19:13:08 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Get current time in milliseconds.
 * @return Current time in ms since Epoch.
 */
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	get_sim_time(t_args *args)
{
	return (get_time_ms() - args->philos->t_start);
}

/**
 * @brief Sleeps for @p ms milliseconds unless simulation stops.
 *
 * Checks @p args->simulation_stopped every 100µs to allow early exit,
 * ensuring actions can stop promptly when the simulation ends.
 *
 * @param args Simulation arguments containing the stop flag.
 * @param ms   Sleep duration in milliseconds.
 */
void	smart_sleep(t_args *args, long ms)
{
	long	wake_up;

	wake_up = get_sim_time(args) + ms;
	while (!args->simulation_stopped 
		&& get_sim_time(args) < wake_up)
		usleep(100);
}

/**
 * @brief Synchronizes all threads to start at the same time.
 *
 * Busy-waits until the specified absolute start time in milliseconds,
 * ensuring all philosopher threads begin execution simultaneously.
 *
 * @param target_time_ms Absolute time in milliseconds to wait for.
 */
void	wait_for_start(long target_time_ms)
{
	while (get_time_ms() < target_time_ms)
		usleep(100);
}
