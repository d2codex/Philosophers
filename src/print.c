/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:45:32 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 11:32:26 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Safely prints a philosopher's action with timestamp.
 *
 * This function locks the shared print mutex to prevent data races.
 * If the action is DIED, it is printed immediately and the simulation
 * is marked as stopped. Once the simulation is stopped, no further
 * messages will be printed from any philosopher.
 *
 * @param philo Pointer to the philosopher performing the action.
 * @param action The action/state to print (e.g., THINKING, EATING, DIED).
 */
void	print_display_msg(t_philo *philo, t_state action)
{
	long	time;

	pthread_mutex_lock(&philo->args->print_lock);

	if (is_simulation_stopped(philo->args) && action != DIED)
	{
		pthread_mutex_unlock(&philo->args->print_lock);
		return ;
	}
	time = get_sim_time(philo->args);
	if (action == DIED)
	{
		printf("%ld %d died\n", time, philo->id);
		set_simulation_stopped(philo->args, true);
	}
	else if (action == THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (action == GOT_FORK1 || action == GOT_FORK2)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (action == EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (action == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
}
