/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:08 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/02 14:31:08 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fi_init_pipex(t_var *p)
{
	p->infd = 0;
	p->outfd = 0;
	p->i = 0;
	p->argv = NULL;
	p->path = NULL;
	p->option = NULL;
	p->path_f = NULL;
	p->cmd_i = NULL;
	p->path_j = NULL;
}

void	ft_pipex(t_var *p, char **envp, int argc, char **argv)
{
	int outfd;
	int pipe_fd[2];
	int	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0) //child
	{
		close(pipe_fd[0]);
		if(p->i == argc - 2)
		{
			outfd = open(argv[p->i + 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
			dup2(outfd, 1);
		}
		else
			dup2(pipe_fd[1], 1);
		execve(p->path, p->option, envp);
		exit(127);
	} 
	else 
	{
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

char	*ft_chk_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK | R_OK | X_OK) == 0)
			return (path[i]);
		i++;
	}
	perror("aow mai na mun mai mee!!!!");
	return (NULL);
}

size_t	ft_str_count(char **path)
{
	size_t	i;

	i = 0;
	while (path[i] != NULL)
		i++;
	return (i);
}

char	*ft_join_path(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	i = (ft_strlen(s1) + ft_strlen(s2) + 1);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	j = -1;
	k = -1;
	while (s1[++j])
		str[j] = s1[j];
	str[j++] = '/';
	while (s2[++k])
		str[j+k] = s2[k];
	str[i + 1] = '\0';
	return ((char *)str);
}

char	**ft_set_path(char **cmd, char **envp, t_var *p)
{
	int	i;

	p->cmd_i = ft_split(*cmd, ' ');
	i = -1;
	while (ft_strncmp("PATH", envp[++i], 4) != 0)
		;
	p->path_f = ft_split(envp[i] + 5, ':');
	p->path_j = (char **)malloc(sizeof(char *) * ft_str_count(p->path_f) + 1);
	i = -1;
	while (p->path_f[++i])
		p->path_j[i] = ft_join_path(p->path_f[i], p->cmd_i[0]);
	p->path_j[i + 1] = NULL;
	return (p->path_j);
}



int	main(int argc, char **argv, char **envp)
{
	t_var	p;

	fi_init_pipex(&p);
	p.i = 2;
	p.infd = open(argv[1], O_RDONLY);
	if (p.infd < 0)
	{
		perror("file not found");
		exit(2);
	}
	dup2(p.infd, 0);	
	while (p.i <= argc - 2)
	{
		p.path = ft_chk_path(ft_set_path(&argv[p.i], envp, &p));
		p.option = ft_split(argv[p.i], ' ');
		ft_pipex(&p, envp, argc, argv);
		p.i++;
	}




	return (0);
}