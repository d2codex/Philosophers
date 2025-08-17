/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:28:10 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/17 12:13:37 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdbool.h>
/**
 * @brief Checks if any philosopher has starved.
 *
 * Iterates through all philosophers and compares the time since their last meal
 * to time_til_death. Returns a pointer to the first philosopher that exceeded
 * the limit, or NULL if none have starved.
 *
 * @param args Pointer to t_args containing philosophers and timing info.
 * @return Pointer to the starving philosopher, or NULL if all are alive.
 */
t_philo	*check_starvation(t_args *args)
{
	long	now;
	int	i;

	now = get_time_ms();
	i = 0;
	while (i < args->num_philos)
	{
		if (now - args->philos[i].t_last_meal_start
			> args->time_til_death)
			return (&args->philos[i]);
		i++;
	}
	return (NULL);
}

/**
 * @brief Checks if all philosophers have reached their meal goal.
 *
 * Loops through all philosophers and verifies if each has eaten at least
 * `meal_goal` times. If any philosopher hasn't, it returns 0. Otherwise, returns 1.
 *
 * @param args Pointer to t_args containing philosophers and meal goal.
 * @return 1 if all have met the goal, 0 otherwise.
 */
int	check_meal_goal(t_args *args)
{
	int	i;

	if (args->meal_goal <= 0)
		return (0);
	i = 0;
	while (i < args->num_philos)
	{
		if (args->meal_goal > 0 &&
			args->philos[i].meals_eaten < args->meal_goal)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Continuously monitors philosophers for death or meal completion.
 *
 * This function runs in its own thread. It repeatedly checks if any philosopher
 * has starved using check_starvation(), or if all have met their meal goals
 * using check_meal_goal(). If a philosopher dies, it prints the death message
 * and stops the simulation. If the meal goal is reached, it stops the simulation.
 *
 * @param arg Pointer to t_args containing simulation info and philosophers array.
 * @return Always returns NULL (thread exit).
 */
void	*monitor(void *arg)
{
	t_args *args = (t_args *)arg;
	t_philo	*dead;

	wait_for_start(args->philos[0].t_start);
	while (!args->simulation_stopped)
	{
		dead = check_starvation(args);
		if (dead)
		{
			print_display_msg(dead, DIED);
			args->simulation_stopped = true;
			return (NULL);
		}
		if (check_meal_goal(args))
		{
			args->simulation_stopped = true;
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
