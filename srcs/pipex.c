/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:04:05 by vsedat            #+#    #+#             */
/*   Updated: 2022/02/28 13:22:28 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"
/*
void	child_one(int f1, char *cmd1, int *end, char **envp)
{
	char	**splited;

	splited = ft_split(cmd1, ' ');
	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	dprintf(2, "%s$\n", cmd1);
	dprintf(2, "%s$\n", path(splited[0], envp));
	if (cmd1 && path(splited[0], envp))
		execve(path(splited[0], envp), splited, envp);
	else
		errorcmd(splited);
}

void	child_two(int f2, char *cmd2, int *end, char **envp)
{
	char	**splited;

	splited = ft_split(cmd2, ' ');
	dup2(f2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	if (cmd2 && path(splited[0], envp))
		execve(path(splited[0], envp), splited, envp);
	else
		errorcmd(splited);
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	int	end[2];
	int	id1;
	int	id2;

	if (pipe(end) < 0)
		terminate();
	id1 = fork();
	if (id1 < 0)
		return (perror("Fork: "));
	if (id1 == 0)
		child_one(f1, argv[2], end, envp);
	id2 = fork();
	if (id2 < 0)
		return (perror("Fork: "));
	if (id2 == 0)
		child_two(f2, argv[3], end, envp);
	close(end[0]);
	close(end[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	int		status;

	if (argc != 5)
		return (write(2, "usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (1);
	pipex(f1, f2, argv, envp);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (0);
}
*/

void	child_one(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	c_pid;

	c_pid = fork();
	if (c_pid < 0)
		terminate();
	if (c_pid == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			terminate();
		cmd = ft_split(av[2], ' ');
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if (cmd[0] && path(cmd[0], envp))
		{
			execve(path(cmd[0], envp), cmd, envp);
			free_split(cmd);
		}
		else
			errorcmd(cmd);
	}
}

void	child_two(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	c_pid;

	c_pid = fork();
	if (c_pid < 0)
		terminate();
	if (c_pid == 0)
	{
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			terminate();
		cmd = ft_split(av[3], ' ');
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (cmd[0] && path(cmd[0], envp))
		{
			execve(path(cmd[0], envp), cmd, envp);
			free_split(cmd);
		}
		else
			errorcmd(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	fd[2];
	int	status;

	if (ac != 5)
		return (write(2, "usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45));
	if (pipe(pipefd) < 0)
		terminate();
	child_one(pipefd, fd, av, envp);
	child_two(pipefd, fd, av, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (0);
}
