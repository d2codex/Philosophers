/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:29:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/14 17:01:50 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>

void	philo_routine(t_philo *philo)
{
	wait_for_start(philo->t_start);
	philo->t_last_meal_start = get_time_ms();
	while (!philo->args->simulation_stopped)
	{
		grab_forks(philo);
		eat(philo);
		slumber(philo);
		think(philo);

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
void	slumber(t_philo *philo)
{
	philo->state = SLEEPING;
	print_display_msg(philo, SLEEPING);
	smart_sleep(philo->args, philo->args->sleep_time);
}

/**
 * @brief Makes a philosopher think safely before eating again.
 *
 * Calculates remaining time before death minus a margin and sleeps that long.
 * Skips thinking if the time is zero or negative. Updates state and prints
 * only if actually thinking.
 *
 * @param philo The philosopher to think.
 */
void	think(t_philo *philo)
{
	long	now;
	long	elapsed_since_last_meal;
	long	time_left;
	long	think_time;

	now = get_time_ms();
	elapsed_since_last_meal = now - philo->t_last_meal_start;
	time_left = philo->args->time_til_death - elapsed_since_last_meal;
	think_time = time_left - ACQUIRE_MARGIN;
	if (think_time < 0)
		think_time = 0;
	else
	{
		philo->state = THINKING;
		print_display_msg(philo, THINKING);
		smart_sleep(philo->args, think_time);
	}
}
