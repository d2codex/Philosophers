/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:53:14 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/08 12:05:56 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Parses and validates command-line arguments into the args struct.
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
 * @todo Make error_return function to save lines.
 */
int	parse_init_args(int ac, char **av, t_args *args)
{
	args->meal_goal = -1;

	if (ac < 5 || ac > 6)
	{
		write(2, "error1\n", 7);
		return (1);
	}
	if (!ft_safe_atoi(av[1], &args->philos))
	{
		write(2, "error2\n", 7);
		return (1);
	}
	if (args->philos < 1)
		return (1);
	if (!ft_atosize(av[2], &args->time_til_death))
	{
		write(2, "error3\n", 7);
		return (1);
	}
	if (!ft_atosize(av[3], &args->eat_time))
	{
		write (2, "error4\n", 7);
		return (1);
	}
	if (!ft_atosize(av[4], &args->sleep_time))
	{
		write (2, "error4\n", 7);
		return (1);
	}
	if (ac == 6)
	{
		if (!ft_safe_atoi(av[5], &args->meal_goal))
		{
			write(2, "error5\n", 7);
			return (1);
		}
		if (args->meal_goal < 0)
			return (1);
	}
	return (0);
}

