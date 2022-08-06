/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:08 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/06 16:00:50 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **cmd;

int	ft_heredoc_pipex(char **argv, int argc, t_var *p)
{
	if(argc < 6)
	{
		write(1, "argument error", 14);
		return(0);
	}
	p->herefd = open("here_doc", O_CREAT | O_RDWR| O_APPEND, 777);
	while (1)
	{
		p->line = get_next_line(0);
		if(ft_strncmp(argv[2], p->line, ft_strlen(argv[2])) == 0)
			break;
		write(p->herefd, p->line, ft_strlen(p->line));
		free(p->line);
	}
	dup2(p->herefd , 0);
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
		return(0);
	}
	return(0);
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

void	ft_pipex(t_var *p, char **envp, int argc, char **argv)
{
	pipe(p->pipe_fd);
	p->pid = fork();
	if (p->pid == 0)
	{
		close(p->pipe_fd[0]);
		if(p->i == argc - 2)
		{
			p->outfd = open(argv[p->i + 1],\
			 O_CREAT | O_WRONLY | O_TRUNC , 0644);
			dup2(p->outfd, 1);
		}
		else
			dup2(p->pipe_fd[1], 1);
		execve(p->path, cmd, envp);
		exit(127);
	} 
	else 
	{
		waitpid(p->pid, NULL, 0);
		close(p->pipe_fd[1]);
		dup2(p->pipe_fd[0], 0);
	}
}

int	ft_chk_path(char **path_a, t_var *p)
{
	int	i;

	i = 0;
	while (path_a[i])
	{
		if (access(path_a[i], F_OK | R_OK | X_OK) == 0)
			return (i);
		i++;
	}
	perror("aow mai na mun mai mee!!!!\n");
	ft_free_pipex(p);
	exit(0);
}

size_t	ft_str_count(char **path_c)
{
	size_t	i;

	i = 0;
	while (path_c[i] != NULL)
		i++;
	return (i);
}

//                         grep qw
char	*ft_set_path(char **cmd_p, char **envp, t_var *p)
{
	int	i;
	// cmd = { "grep","qw", NULL}
	cmd = ft_split(*cmd_p, ' ');
	i = -1;
	while (ft_strncmp("PATH", envp[++i], 4) != 0)
		;
	p->path_f = ft_split_join(envp[i] + 5, ':', cmd[0]);
	return (p->path_f[ft_chk_path(p->path_f, p)]);
}
void	ft_free_pipex(t_var *p)
{
	int	i;

	i=-1;
	while(p->path_f[++i])
		free(p->path_f[i]);
	free(p->path_f);
	i=-1;
	while(cmd[++i])
		free(cmd[i]);
	free(cmd);
	p->path = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_var	p;

	ft_init_pipex(&p);
	if (ft_strncmp("here_doc", argv[1], 7) == 0)
		p.i = ft_heredoc_pipex(argv, argc, &p);
	p.infd = open(argv[1], O_RDONLY);
	ft_chk_input(argc, p.infd);
	dup2(p.infd, 0);	
	while (p.i <= argc - 2)
	{
		p.path = ft_set_path(&argv[p.i], envp, &p);
		ft_pipex(&p, envp, argc, argv);
		ft_free_pipex(&p);
		p.i++;
	}
	return (0);
}