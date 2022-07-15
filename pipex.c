/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:08 by psuanpro          #+#    #+#             */
/*   Updated: 2022/07/14 13:35:59 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	chk_path(char	**s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strncmp(s[i], "PATH", 4) == 0)
			break;
		i++;
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)**argv;
	int	i = 0;
	char *options[3] = {"ls", "-la", NULL};
	char	**path;
	char	**pathj;
	printf("%d\n", i);

		
	pathj = (char **)malloc(sizeof(char *));

	path = ft_split(envp[chk_path(envp)]+5,':');
	while (path[i]){
		printf("path = |%s|\n", path[i]);
		i++;
	}
	i = 0;
	while (path[i])
	{
		pathj[i] = ft_strjoin(path[i], "/ls");
		i++;
	}
	while (*pathj)
	{
		execve(*pathj, options , envp);
		// printf("envp %s\n", *envp);
		pathj++;
	}
	return 0;
}

// > ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2