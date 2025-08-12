/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:30:54 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/12 19:02:00 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	pthread_mutex_t	*forks;
	t_philo		*philos;

	if (parse_init_args(ac, av, &args) != 0)
		return (print_usage(), 1);
	if (validate_args(&args) != 0)
		return (print_usage(), 1);
	if (init_forks(&forks, args.philos) != 0)
		return (1);
	if (init_philos(&philos, &args, forks) != 0)
		return (1);
	return (0);
}

