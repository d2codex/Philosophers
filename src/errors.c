/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:51:59 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/08 14:05:01 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Writes an error message to stderr and returns a code.
 *
 * @param[in] msg Error message string to print.
 * @param[in] ret Return code to return.
 *
 * @return Returns the given return code.
 */
int	error_return(const char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	return (ret);
}
