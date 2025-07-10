/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:06:27 by jinxu             #+#    #+#             */
/*   Updated: 2025/07/11 00:28:37 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static char	*verify_path(char *cmd, char **split_paths)
{
	char	*full_path;
	char	*prefix;
	int		i;

	i = 0;
	while (split_paths[i])
	{
		prefix = ft_strjoin(split_paths[i], "/");
		if (!prefix)
			return (NULL);
		full_path = ft_strjoin(prefix, cmd);
		free(prefix);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		else
			free(full_path);
		i++;
	}
	return (NULL);
}

static char	*search_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (envp[i]);
}

char	*find_path(char *cmd, char **envp)
{
	char	*line;
	char	*trimmed_path;
	char	**split_paths;
	char	*cmd_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	cmd_path = NULL;
	line = search_env(envp);
	trimmed_path = ft_substr(line, 5, ft_strlen(line) - 5);
	if (!trimmed_path)
		return (NULL);
	split_paths = ft_split(trimmed_path, ':');
	free(trimmed_path);
	if (!split_paths)
		return (NULL);
	cmd_path = verify_path(cmd, split_paths);
	ft_free(split_paths);
	return (cmd_path);
}
