/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:42:55 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/08 16:45:59 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_heredoc_pipex(char **argv, int argc, t_var *p)
{
	if (argc < 6)
	{
		write(1, "argument error", 14);
		return (0);
	}
	p->herefd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 777);
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		p->line = get_next_line(0);
		if (ft_strncmp(argv[2], p->line, ft_strlen(argv[2])) == 0)
			break ;
		write(p->herefd, p->line, ft_strlen(p->line));
		free(p->line);
	}
	dup2(p->herefd, 0);
	return (3);
}

int	ft_chk_input(int anum, int numfd)
{
	if (numfd < 0)
	{
		perror("file not found");
		exit(2);
	}
	else if (anum < 5)
	{
		write(1, "argument error", 14);
		return (0);
	}
	return (0);
}

void	ft_init_pipex(t_var *p)
{
	p->infd = 0;
	p->outfd = 0;
	p->herefd = 0;
	p->i = 2;
	p->argv = NULL;
	p->path = NULL;
	p->path_f = NULL;
}

void	ft_read_outfile(t_var *p, char **argv)
{
	if (ft_strncmp("here_doc", argv[1], 7) == 0)
	{
		p->outfd = open(argv[p->i + 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		p->outfd = open(argv[p->i + 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	dup2(p->outfd, 1);
}

void	ft_pipex(t_var *p, char **envp, int argc, char **argv)
{
	pipe(p->pipe_fd);
	p->pid = fork();
	if (p->pid == 0)
	{
		close(p->pipe_fd[0]);
		if (p->i == argc - 2)
			ft_read_outfile(p, argv);
		else
			dup2(p->pipe_fd[1], 1);
		execve(p->path, p->cmd, envp);
		exit(127);
	}
	else
	{
		waitpid(p->pid, NULL, 0);
		close(p->pipe_fd[1]);
		dup2(p->pipe_fd[0], 0);
	}
}
