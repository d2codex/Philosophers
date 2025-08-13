/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/13 16:38:59 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief Sleeps for @p ms milliseconds unless simulation stops.
 *
 * Checks @p args->simulation_stopped every 500µs to allow early exit,
 * ensuring actions can stop promptly when the simulation ends.
 *
 * @param args Simulation arguments containing the stop flag.
 * @param ms   Sleep duration in milliseconds.
 */
void	smart_sleep(t_args *args, long ms)
{
	long	start;
	long	now;

	start = get_time_ms();
	while (!args->simulation_stopped)
	{
		now = get_time_ms();
		if (now - start > ms)
			break ;
		usleep(500);
	}
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
