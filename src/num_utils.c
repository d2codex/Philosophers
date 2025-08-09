/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:01:03 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/09 21:03:41 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_utils.h"
#include <limits.h>

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

/**
 * @brief Safely converts a string to an int.
 *
 * Allows leading and trailing whitespace, supports an optional '+' or '-'
 * and ensures the input is a valid integer within `INT_MIN` to `INT_MAX`.
 *
 * @param str Input string to convert.
 * @param out Pointer to store the result.
 * @return 1 on success, 0 on failure.
 */
int	ft_safe_atoi(const char *str, int *out)
{
	long	result;
	int	sign;
	
	if (!str || !out)
		return 0;
	str = skip_spaces(str);
	sign = parse_sign(&str);
	if (!ft_isdigit(*str))
		return (0);
	result = 0;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && result > (long)INT_MAX + 1))
            		return (0);
		str++;
	}
	str = skip_spaces(str);
	if (*str != '\0')
		return (0);
	*out = result * sign;
	return (1);
}

/**
 * @brief Safely converts a string to size_t.
 *
 * @details
 * Allows leading and trailing whitespaces, accepts an optional '+'.
 * Fails on overflow, invalid characters, or if the input is NULL,
 * empty, or just a '+'.
 *
 * @param str Input string to parse.
 * @param out Output pointer to store the result.
 * @return 1 on success, 0 on failure.
 */
int	ft_atosize(const char *str, size_t *out)
{
	size_t	result;

	if (!str || !out)
		return (0);
	str = skip_spaces(str);
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	result = 0;
	while (ft_isdigit(*str))
	{
		if (result > (SIZE_MAX - (*str - '0')) / 10)
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	str = skip_spaces(str);
	if (*str != '\0')
		return (0);
	*out = result;
	return (1);
}
