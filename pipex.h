/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:45:04 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/08 16:46:54 by psuanpro         ###   ########.fr       */
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
	char	**argv;
	char	*path;
	char	**option;
	char	**path_f;
	char	**cmd;
	char	*line;
	int		infd;
	int		outfd;
	int		i;
	int		herefd;
	int		pipe_fd[2];
	int		pid;
}	t_var;

char	**ft_split_join(char const *s, char c, char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int		ft_chk_input(int anum, int numfd);
int		ft_chk_path(char **path_a, t_var *p);
int		ft_heredoc_pipex(char **argv, int argc, t_var *p);
void	ft_pipex(t_var *p, char **envp, int argc, char **argv);
size_t	ft_str_count(char **path_c);
char	*ft_set_path(char **cmd_p, char **envp, t_var *p);
void	ft_free_pipex(t_var *p);
void	ft_read_outfile(t_var *p, char **argv);
void	ft_init_pipex(t_var *p);
#endif