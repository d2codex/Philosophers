/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:34:23 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/09 21:28:20 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/**
 * @brief Initializes an array of mutexes representing chopsticks (cs).
 *
 * Allocates memory for `num_philos` mutexes and initializes each one in
 * the unlocked state.
 * If allocation or initialization fails, previously initialized mutexes
 * are destroyed and memory is freed.
 *
 * @param cs Pointer to the array of mutexes to allocate and initialize.
 * @param num_philos Number of mutexes (chopsticks) to create.
 *
 * @return 0 on success, 1 on failure.
 */
int	init_chopsticks(pthread_mutex_t **cs, int num_philos)
{
	int	i;

	*cs = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!*cs)
		return (error_return("Failed to malloc for cs\n"));
	i = 0;
	while (i < num_philos)
	{
		if(pthread_mutex_init(&(*cs)[i], NULL) != 0)
		{
			while (--i >=0)
				pthread_mutex_destroy(&(*cs)[i]);
			free(*cs);
			*cs = NULL;
			return (error_return("Mutex init failed\n"));
		}
		i++;
	}
	return (0);
}
