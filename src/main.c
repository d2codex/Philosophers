/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/10 10:23:18 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	pthread_mutex_t	*cs;

	if (parse_init_args(ac, av, &args) != 0)
		return (print_usage(), 1);
	if (validate_args(&args) != 0)
		return (print_usage(), 1);
	if (init_chopsticks(&cs, args.philos) != 0)
		return (1);
//test args 1
/*
	printf("number of philos: %d\n", args.philos);
	printf("time_til_death in ms: %zu\n", args.time_til_death);
	printf("eat_time in ms: %zu\n", args.eat_time);
	printf("sleep_time in ms: %zu\n", args.sleep_time);
	if (ac == 6)
		printf("meal_goal: %d\n", args.meal_goal);
*/
// test fork mutex 
/*
	int i = 0;
	while (i < args.philos)
	{
		printf("chopstick[%d]: %p\n", i + 1, (void *)&cs[i]);
		i++;
	}
*/
	return (0);
}

