/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:18:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/08 12:05:34 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <stddef.h>
# include <pthread.h>

/**
 * @enum t_state
 * @brief Represents the different states a philosopher can be in.
 */
typedef	enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
}	t_state;

/**
 * @struct t_args
 * @brief Configuration arguments for the philosophers simulation.
 *
 * @var s_args::philos
 * Number of philosophers.
 * Stored as int for easy looping and validation (philos >= 1).
 *
 * @var s_args::time_til_death
 * Time in milliseconds until starvation.
 * Stored as size_t since time is always non-negative.
 *
 * @var s_args::eat_time
 * Eating duration in milliseconds.
 * Stored as size_t for the same reason as time_til_death.
 *
 * @var s_args::sleep_time
 * Sleeping duration in milliseconds.
 * Stored as size_t for the same reason as time_til_death.
 *
 * @var s_args::meal_goal
 * Number of meals before simulation ends.
 * Stored as int to allow -1 as "no goal" and easy decrementing.
 */
typedef struct	s_args
{
	int	philos;
	size_t	time_til_death;
	size_t	eat_time;
	size_t	sleep_time;
	int	meal_goal;
}	t_args;

/**
 * @struct t_philo
 * @brief Represents a philosopher in the simulation.
 *
 * @var s_philo::id
 * Unique identifier for the philosopher.
 * @var s_philo::left_cs
 * Index of the left chopstick.
 * @var s_philo::right_cs
 * Index of the right chopstick.
 * @var s_philo::thread
 * Thread associated with this philosopher.
 * @var s_philo::state
 * Current state of the philosopher (eating, sleeping, thinking).
 * @var s_philo::meals_eaten
 * Number of meals this philosopher has consumed.
 * @var s_philo::last_eat_time
 * Timestamp (in milliseconds) of last meal start.
 * @var s_philo::args
 * Pointer to shared arguments/configuration.
 */
typedef struct	s_philo
{
	int		id;
	int		left_cs;
	int		right_cs;
	pthread_t	thread;
	t_state		state;
	int		meals_eaten;
	long long	time_last_eaten;
	t_args		*args;
}	t_philo;

// prototypes for parse.c
int     parse_init_args(int ac, char **av, t_args *args);

#endif
