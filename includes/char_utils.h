/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:46:22 by diade-so          #+#    #+#             */
/*   Updated: 2025/08/09 20:36:01 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_H
# define CHAR_UTILS_H

# include <stddef.h>
# include <ctype.h>
# include <limits.h>
# include <stdint.h>

int     ft_isdigit(int c);
int     ft_isspace(char c);
const char *skip_spaces(const char *str);
size_t  ft_strlen(const char *s);

#endif
