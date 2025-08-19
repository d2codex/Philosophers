/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:28:10 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/19 12:15:58 by diade-so         ###   ########.fr       */
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

	now = get_sim_time(args);
	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_lock(&args->philos[i].meal_lock);
		if (now - args->philos[i].t_last_meal_start
			> args->time_til_death)
		{
			pthread_mutex_unlock(&args->philos[i].meal_lock);
			return (&args->philos[i]);
		}
		pthread_mutex_unlock(&args->philos[i].meal_lock);
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
		pthread_mutex_lock(&args->philos[i].meal_lock);
		if (args->meal_goal > 0 &&
			args->philos[i].meals_eaten < args->meal_goal)
		{
			pthread_mutex_unlock(&args->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&args->philos[i].meal_lock);
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
	while (!is_simulation_stopped(args))
	{
		dead = check_starvation(args);
		if (dead)
		{

			print_display_msg(dead, DIED);
			set_simulation_stopped(args, true);
			return (NULL);
		}
		if (check_meal_goal(args))
		{
			set_simulation_stopped(args, true);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

/**
 * @brief Check if the simulation has been stopped.
 *
 * This function reads the simulation_stopped flag
 * using the stop_lock mutex to avoid race conditions.
 *
 * @param args Pointer to the simulation arguments structure.
 * @return true if the simulation is stopped, false otherwise.
 */
bool	is_simulation_stopped(t_args *args)
{
	bool	stopped;

	pthread_mutex_lock(&args->stop_lock);
	stopped = args->simulation_stopped;
	pthread_mutex_unlock(&args->stop_lock);
	return (stopped);
}

/**
 * @brief Sets the simulation stopped flag.
 *
 * This function updates the simulation_stopped flag
 * while holding the stop_lock mutex to prevent race conditions.
 *
 * @param args  Pointer to the simulation arguments structure.
 * @param value Boolean value to set the simulation_stopped flag.
 */
void	set_simulation_stopped(t_args *args, bool value)
{
	pthread_mutex_lock(&args->stop_lock);
	args->simulation_stopped = value;
	pthread_mutex_unlock(&args->stop_lock);
}
