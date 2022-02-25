/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:39:51 by vsedat            #+#    #+#             */
/*   Updated: 2022/02/25 14:40:23 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	<stdio.h>
# include	<fcntl.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/wait.h>

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**get_paths(char **envp);
char	*path(char *cmd, char **envp);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	free_split(char **args);
void	usage(void);
void	terminate(void);
void	cmd_not_found(char **cmd);

#endif
