/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:14:20 by jinxu             #+#    #+#             */
/*   Updated: 2025/05/11 18:38:40 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);
int	print_char(int c, int *err);
int	print_nbr(long nbr, int *err);
int	print_str(char *str, int *err);
int	print_unsignedint(unsigned int nbr, int *err);
int	print_hex(unsigned int n, int is_upper, int *err);
int	print_ptr(uintptr_t ptr, int *err);

#endif
