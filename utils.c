/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:06:27 by jinxu             #+#    #+#             */
/*   Updated: 2025/07/11 00:42:39 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	redirect_io(int input_fd, int output_fd)
{
	int	i;
	int	j;

	i = dup2(input_fd, 0);
	j = dup2(output_fd, 1);
	if (i < 0 || j < 0)
	{
		perror("dup2 fails");
		exit(EXIT_FAILURE);
	}
}

void	ft_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	exit_with_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
