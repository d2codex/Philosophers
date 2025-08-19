/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:51:59 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 12:40:57 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "char_utils.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Writes an error message to stderr.
 *
 * @param[in] msg Error message string to print.
 * @param[in] ret Return code to return.
 *
 * @return Returns 1 on succes, 0 on failure.
 */
int	error_return(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	print_usage()
{
	char	*usage;

	usage = "usage: ./philo <philos> <time_til_death> <eat_time> "
		"<sleep_time> [meal_goal]\n";
	write (2, usage, ft_strlen(usage));
}

/**
 * @brief Cleans up allocated resources and optionally prints an error message.
 *
 * This function frees the philosopher array, destroys all fork mutexes,
 * frees the fork array, and destroys the print mutex. It can also
 * print a custom message if provided, which is useful for error reporting.
 *
 * @param args Pointer to the t_args struct containing simulation data.
 * @param forks Pointer to the array of fork mutexes to destroy and free.
 * @param msg Optional message to print (e.g., error message). Can be NULL.
 */
void	cleanup(t_args *args, pthread_mutex_t *forks, const char *msg)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	if (args && args->philos)
		free(args->philos);
	if (forks)
	{
		i = 0;
		while (i < args->num_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	if (args)
		pthread_mutex_destroy(&args->print_lock);
}

/**
 * @brief Destroy all mutexes used in the simulation.
 *
 * Cleans up the stop_lock, print_lock, all fork mutexes,
 * and each philosopher's meal_lock to prevent resource leaks.
 *
 * @param args Pointer to the simulation arguments structure.
 */
void	destroy_mutexes(t_args *args)
{
	int	i;

	pthread_mutex_destroy(&args->stop_lock);
	pthread_mutex_destroy(&args->print_lock);
	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_destroy(&args->philos[i].meal_lock);
		i++;
	}
}
