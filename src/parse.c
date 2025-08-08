/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:53:14 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/08 13:58:39 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Parses command-line arguments into the args struct.
 *
 * Converts input strings to appropriate types and initializes args.
 *
 * @param[in] ac Argument count.
 * @param[in] av Argument values.
 * @param[out] args Pointer to t_args to initialize.
 * 
 * @return 0 on success, 1 on failure (invalid args or parse error).
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
	if (ac < 5 || ac > 6)
		return (error_return("Invalid number of arguments\n", 1));
	if (!ft_safe_atoi(av[1], &args->philos))
		return (error_return("Invalid number of philosophers\n", 1));
	if (!ft_atosize(av[2], &args->time_til_death))
		return (error_return("Invalid time til death\n", 1));
	if (!ft_atosize(av[3], &args->eat_time))
		return (error_return("Invalid eat time\n", 1));
	if (!ft_atosize(av[4], &args->sleep_time))
		return (error_return("Invalid sleep time\n", 1));
	if (ac == 6)
	{
		if (!ft_safe_atoi(av[5], &args->meal_goal))
			return (error_return("Invalaid meal_goal input\n", 1));
		if (args->meal_goal == -1)
			return (error_return("Meal goal must be >= 0\n", 1));
	}
	else
		args->meal_goal = -1;
	return (0);
}

/**
 * @brief Validates the logical correctness of parsed arguments.
 *
 * Checks that values meet project constraints, such as:
 * - philosophers count >= 1
 * - time durations > 0
 * - meal goal >= 0 if specified
 *
 * @param[in] args Pointer to the parsed arguments structure.
 *
 * @return 0 if all values are valid, 1 otherwise (prints error messages).
 */
int	validate_args(t_args *args)
{

	if (args->philos < 1)
		return (error_return("Philosophers must be >= 1\n", 1));
	if (args->time_til_death == 0)
		return (error_return("Time til death must be > 0\n", 1));
	if (args->eat_time == 0)
		return (error_return("Eat duration must be > 0\n", 1));
	if (args->sleep_time == 0)
		return (error_return("Sleep duration must be > 0\n", 1));
	if (args->meal_goal != -1 && args->meal_goal < 0)
		return (error_return("Meal goal must be >= 0\n", 1));
	return (0);
}
