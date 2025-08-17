/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:29:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/17 22:01:03 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Main routine executed by each philosopher thread.
 *
 * Waits for the synchronized start, staggers even philosophers,
 * and loops through eating, sleeping, and thinking until the
 * simulation stops or the meal goal is reached.
 *
 * @param philo Pointer to the philosopher's state and data.
 */
void	philo_routine(t_philo *philo)
{
	wait_for_start(philo->t_start);
	if (philo->id % 2 == 0) // stagger evens, so odds can eat first
		smart_sleep(philo->args, philo->args->eat_time / 10);
	//philo->t_last_meal_start = get_time_ms(); why am i resetting here? not needed
	while (!philo->args->simulation_stopped)
	{
		if (philo->args->meal_goal > 0 &&
			philo->meals_eaten >= philo->args->meal_goal)
			break ;
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
	if (philo->id % 2 == 0) //evens grab fork1 first, odds fork2
	{
		pthread_mutex_lock(philo->fork1);
		print_display_msg(philo, GOT_FORK1);
		pthread_mutex_lock(philo->fork2);
		print_display_msg(philo, GOT_FORK2);
	}
	else
	{
		pthread_mutex_lock(philo->fork2);
		print_display_msg(philo, GOT_FORK2);
		pthread_mutex_lock(philo->fork1);
		print_display_msg(philo, GOT_FORK1);
	}
}

/**
 * @brief Philosopher starts eating and immediately increments meal count,
 * then sleeps for the configured eat time (smart_sleep checks for simulation stop)
 * and releases the forks.
 * @param philo Pointer to the philosopher structure.
 */
void	eat(t_philo *philo)
{
	philo->state = EATING;
	philo->t_last_meal_start = get_sim_time(philo->args);
	philo->meals_eaten++;
	print_display_msg(philo, EATING);
	smart_sleep(philo->args, philo->args->eat_time);
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

	now = get_sim_time(philo->args);
	elapsed_since_last_meal = now - philo->t_last_meal_start;
	time_left = philo->args->time_til_death - elapsed_since_last_meal;
	think_time = time_left /*- ACQUIRE_MARGIN*/;
	if (think_time < 0)
		think_time = 0;
	else
	{
		philo->state = THINKING;
		print_display_msg(philo, THINKING);
		smart_sleep(philo->args, think_time);
	}
}
