/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:38 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/03 13:55:47 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "get_next_line.h"


typedef struct s_var {
	int	infd;
	int	outfd;
	int	argc;
	int	i;
	int herefd;
	char	**argv;
	char	*path;
	char	**option;
	char	**path_f;
	char	**cmd_i;
	char	**path_j;
	char	*line;
} t_var;

void	fi_init_pipex(t_var *p);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
//test function
char	**ft_set_path(char **cmd, char **envp, t_var *p);
char	*ft_join_path(char *s1, char *s2);
char	*ft_chk_path(char **path);
size_t	ft_str_count(char **path);
int	ft_chk_input(int anum, int numfd);
int	ft_heredoc_pipex(char *argv, int argc, t_var *p);
#endif
