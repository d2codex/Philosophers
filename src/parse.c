/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:53:14 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/08 15:05:08 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Parses command-line arguments into the args struct.
 *
 * Converts input strings to appropriate types and initializes args.
 * Prints error messages for every invalid input found when
 * ac is 5 or 6.
 *
 * @param[in] ac Argument count.
 * @param[in] av Argument values.
 * @param[out] args Pointer to t_args to initialize.
 * 
 * @return 0 if all args parsed successfully, 1 on failure if one or more
 * errors occured.
 *
 * @note Time values use size_t for non-negativity;
 * philos and meal_goal use int for easy looping and sentinel values,
 * but reject negative values from user input.
 *
 * @warning Does not perfrom logical validation on the values.
 *
 * @notes Should I allow 0 for sleep duration?? For, now this 
 * function does not allow a 0 sleep time. To sleep or not to sleep -
 * that is the queston! Same for eating..hmm
 */
int	parse_init_args(int ac, char **av, t_args *args)
{
	int	error_found;

	error_found = 0;
	if (ac < 5 || ac > 6)
		return (error_return("Invalid number of arguments\n"), 1);
	if (!ft_safe_atoi(av[1], &args->philos))
		error_found |= error_return("Invalid number of philosophers\n");
	if (!ft_atosize(av[2], &args->time_til_death))
		error_found |= error_return("Invalid time til death\n");
	if (!ft_atosize(av[3], &args->eat_time))
		error_found |= error_return("Invalid eat time\n");
	if (!ft_atosize(av[4], &args->sleep_time))
		error_found |= error_return("Invalid sleep time\n");
	if (ac == 6)
	{
		if (!ft_safe_atoi(av[5], &args->meal_goal))
			error_found |= error_return("Invalaid meal_goal input\n");
		if (args->meal_goal == -1)
			error_found |= error_return("Meal goal must be >= 0\n");
	}
	else
		args->meal_goal = -1;
	return (error_found);
}

/**
 * @brief Validates the logical correctness of parsed arguments.
 *
 * Checks that values meet project constraints, such as:
 * - philosophers count >= 1
 * - time durations > 0
 * - meal goal >= 0 if specified
 * Prints message for each invalid field found.
 *
 * @param[in] args Pointer to the parsed arguments structure.
 *
 * @return 0 if all values are valid, 1 if any validation errors occurred.
 */
int	validate_args(t_args *args)
{
	int	error_found;

	error_found = 0;
	if (args->philos < 1)
		error_found |= error_return("Philosophers must be >= 1\n");
	if (args->time_til_death == 0)
		error_found |= error_return("Time til death must be > 0\n");
	if (args->eat_time == 0)
		error_found |= error_return("Eat duration must be > 0\n");
	if (args->sleep_time == 0)
		error_found |= error_return("Sleep duration must be > 0\n");
	if (args->meal_goal != -1 && args->meal_goal < 0)
		error_found |= error_return("Meal goal must be >= 0\n");
	return (error_found);
}
