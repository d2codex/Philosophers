/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/12 13:29:43 by diade-so         ###   ########.fr       */
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
 * @brief Sleeps for the given duration in milliseconds with active polling
 *        to maintain timing accuracy.
 */
void	smart_sleep(long ms)
{
	long	start;
	start = get_time_ms();
	
	while(get_time_ms() - start < ms)
		usleep(100);
}
