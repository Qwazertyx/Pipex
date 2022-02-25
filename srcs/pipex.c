/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:04:05 by vsedat            #+#    #+#             */
/*   Updated: 2022/02/25 16:02:41 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	child_one(int f1, char *cmd1, int *end, char **envp)
{
	char	**splited;

	splited = ft_split(cmd1, ' ');
	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
//	dprintf(2, "%s\n", cmd1);
//	dprintf(2, "%s\n", path(splited[0], envp));
	if (cmd1 && path(splited[0], envp))
		execve(path(splited[0], envp), &cmd1, envp);
	else
		write(2, ": command not found\n", 20);
	close(f1);
	exit(1);
}

void	child_two(int f2, char *cmd2, int *end, char **envp)
{
	char	**splited;

	splited = ft_split(cmd2, ' ');
	dup2(f2, STDIN_FILENO);
	dup2(end[0], STDOUT_FILENO);
	if (cmd2 && path(splited[0], envp))
		execve(path(splited[0], envp), &cmd2, envp);
	else
		write(2, ": command not found\n", 20);
	close(f2);
	exit(1);
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	int	end[2];
	int	status;
	int	id1;
	int	id2;

	pipe(end);
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
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;

	if (argc != 5)
		return (write(2, "usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (1);
	pipex(f1, f2, argv, envp);
	return (0);
}
