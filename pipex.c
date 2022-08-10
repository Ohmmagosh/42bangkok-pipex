/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:08 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/08 21:45:42 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	perror("aow mai na mun mai mee!!!!");
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

char	*ft_set_path(char **cmd_p, char **envp, t_var *p)
{
	int	i;

	p->cmd = ft_split(*cmd_p, ' ');
	i = -1;
	while (ft_strncmp("PATH", envp[++i], 4) != 0)
		;
	p->path_f = ft_split_join(envp[i] + 5, ':', p->cmd[0]);
	return (p->path_f[ft_chk_path(p->path_f, p)]);
}

void	ft_free_pipex(t_var *p)
{
	int	i;

	i = -1;
	while (p->path_f[++i])
		free(p->path_f[i]);
	free(p->path_f);
	i = -1;
	while (p->cmd[++i])
		free(p->cmd[i]);
	free(p->cmd);
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
	if (ft_strncmp("here_doc", argv[1], 7) == 0)
		unlink("here_doc");
	return (0);
}
