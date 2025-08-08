/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/07 21:21:09 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_args	args;

	if (parse_init_args(ac, av, &args) == 1)
		return (1);
	printf("number of philos: %d\n", args.philos);
	printf("time_til_death in ms: %zu\n", args.time_til_death);
	printf("eat_time in ms: %zu\n", args.eat_time);
	printf("sleep_time in ms: %zu\n", args.sleep_time);
	if (ac == 6)
		printf("meal_goal: %d\n", args.meal_goal);
	return (0);
}

