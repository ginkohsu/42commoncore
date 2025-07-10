/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:06:17 by jinxu             #+#    #+#             */
/*   Updated: 2025/07/11 01:05:16 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	child_exec(char *cmd_str, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd_str, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		write(2, "command not found\n", 18);
		ft_free(args);
		exit(127);
	}
	execve(cmd_path, args, envp);
	free(cmd_path);
	ft_free(args);
	exit_with_error("execve");
}

static void	child_cmd1(int pipefd[2], char **av, char **envp)
{
	int		fd1;

	close(pipefd[0]);
	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
		exit_with_error("open");
	redirect_io(fd1, pipefd[1]);
	close(fd1);
	close(pipefd[1]);
	child_exec(av[2], envp);
}

static void	child_cmd2(int pipefd[2], char **av, char **envp)
{
	int		fd2;

	close(pipefd[1]);
	fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 < 0)
		exit_with_error("open");
	redirect_io(pipefd[0], fd2);
	close(fd2);
	close(pipefd[0]);
	child_exec(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{
		if (pipe(pipefd) < 0)
			exit_with_error("pipe");
		pid1 = fork();
		if (pid1 < 0)
			exit_with_error("fork1");
		if (pid1 == 0)
			child_cmd1(pipefd, av, envp);
		pid2 = fork();
		if (pid2 < 0)
			exit_with_error("fork2");
		if (pid2 == 0)
			child_cmd2(pipefd, av, envp);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		return (0);
	}
	return (1);
}

/*
*| Exit code            | Use case                                              |
*| -------------------- | ----------------------------------------------------- |
*| `EXIT_FAILURE` (`1`) | General internal error (I/O, malloc, fork, etc.)      |
*| `127`                | Command not found (matches shell)                     |
*| `126`                | Command exists but not executable (optional but nice) |
*
* After running the program, immediately run:
* echo $? //This prints the exit status of the last executed command.
* For example: ./pipex in.txt "notacommand" "wc" out.txt
*              echo $? 
*			  (expected 127)
*However, our parent process (the main process) is exiting with 0
*because it doesn’t know about the child's failure.
*We need to use WIFEXITED() && WEXITSTATUS() from <sys/wait.h> 
*to check children exit codes after waitpid.
*/
