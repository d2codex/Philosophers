/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:18:40 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/18 15:53:59 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "char_utils.h"
# include <stddef.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>

/* Small margin to ensure a philo has time to grab forks before dying */
# define ACQUIRE_MARGIN 1

/**
 * @enum t_state
 * @brief Represents the different states a philosopher can be in.
 */
typedef	enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	GOT_FORK1,
	GOT_FORK2,
	DIED,
}	t_state;

typedef struct s_philo t_philo;

/**
 * @struct t_args
 * @brief Configuration arguments for the philosophers simulation.
 *
 * @var s_args::num_philos
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
 * Initialized to -1 to indicate "no meal goal" specified by user.
 * This sentinel clearly distinguishes between no input (-1) and
 * explicit zero or positive values.
 *
 */
typedef struct	s_args
{
	int	num_philos;
	long	time_til_death;
	long	eat_time;
	long	sleep_time;
	int	meal_goal;
	bool		simulation_stopped;
	pthread_mutex_t	print_lock;
	t_philo	*philos;
}	t_args;

/**
 * @struct t_philo
 * @brief Represents a philosopher in the simulation.
 *
 * @var s_philo::id
 * Unique identifier for the philosopher.
 * @var s_philo::fork1
 * Pointer to the mutex representing the lower indexed fork.
 * @var s_philo::fork2
 * Pointer to the mutex representing the higher indexed fork.
 * @var s_philo::thread
 * Thread associated with this philosopher.
 * @var s_philo::state
 * Current state of the philosopher (eating, sleeping, thinking).
 * @var s_philo::meals_eaten
 * Number of meals this philosopher has consumed.
 * @var s_philo::t_last_meal_start
 * Timestamp (in milliseconds) of last meal start.
 * @var s_philo::t_start
 * Simulation start time.
 * @var s_philo::args
 * Pointer to shared arguments/configuration.
 */
typedef struct	s_philo
{
	int		id;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	pthread_t	thread;
	t_state		state;
	int		meals_eaten;
	long		t_last_meal_start;
	long		t_start;
	t_args		*args;
}	t_philo;

// parse.c
int     parse_init_args(int ac, char **av, t_args *args);
int     validate_args(int ac, t_args *args);

// error.c
int     error_return(const char *msg);
void    print_usage();

// init.c
int     init_forks(pthread_mutex_t **cs, int num_philos);
int     init_philos(t_philo **philos, t_args *args, pthread_mutex_t *forks);
void    handle_one_philo(t_args *args);

// num_utils.c
int     ft_safe_atoi(const char *str, int *out);
int     ft_atolong(const char *str, long *out);

// time.c
long    get_time_ms(void);
long    get_sim_time(t_args *args);
void    smart_sleep(t_args *args, long ms);
void    wait_for_start(long target_time_ms);

// print.c
void    print_display_msg(t_philo *philo, t_state action);

// routine.c
void    philo_routine(t_philo *philo);
void    grab_forks(t_philo *philo);
void    eat(t_philo *philo);
void    slumber(t_philo *philo);
void    think(t_philo *philo);

// monitor
t_philo *check_starvation(t_args *args);
int     check_meal_goal(t_args *args);
void    *monitor(void *arg);

#endif
