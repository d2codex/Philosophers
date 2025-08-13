/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:29:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/13 16:54:22 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo)
{
	while (!philo->args->simulation_stopped)
	{
		grab_forks(philo);
		eat(philo);
		//think - will need to calculate dynamic think time..
		//	based on on who is about to die
	}
}

/**
 * @brief Locks both forks for the philosopher, lower number fork first.
 * @param philo Pointer to the philosopher structure.
 */
void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	print_display_msg(philo, GOT_FORK1);
	pthread_mutex_lock(philo->fork2);
	print_display_msg(philo, GOT_FORK2);
}

/**
 * @brief Philosopher eats for the configured time and releases forks.
 * @param philo Pointer to the philosopher structure.
 */
void	eat(t_philo *philo)
{
	philo->state = EATING;
	philo->t_last_meal_start = get_time_ms();
	print_display_msg(philo, EATING);

	smart_sleep(philo->args, philo->args->eat_time);

	philo->meals_eaten++;

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

/**
 * @brief Philosopher sleeps for the configured time.
 * @param philo Pointer to the philosopher structure.
 */
void	sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_display_msg(philo, SLEEPING);
	smart_sleep(philo->args, philo->args->sleep_time);
}

