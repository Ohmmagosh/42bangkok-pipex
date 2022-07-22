/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:08 by psuanpro          #+#    #+#             */
/*   Updated: 2022/07/21 04:43:02 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_join_path(char const *s1, char const *s2)
{
	char	*str1;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = (ft_strlen(s1) + ft_strlen(s2));
	str1 = (char *)malloc(sizeof(char) * i + 2);
	if (!str1)
		return (NULL);
	while (*s1)
		*str1++ = *s1++;
	*str1++ = '/';
	while (*s2)
		*str1++ = *s2++;
	*str1 = '\0';
	str1 = str1 - i;
	return ((char *)str1);
}

void	ft_set_path(char **cmd, char **envp)
{
	int	i;
	char	**path_f;
	char	**cmd_i;
	char	**path_j;

	cmd_i = (char **)malloc(sizeof(char *));
	path_f = (char **)malloc(sizeof(char *));
	path_j = (char **)malloc(sizeof(char *));
	cmd_i = ft_split(*cmd, ' ');
	i = -1;
	while (ft_strncmp("PATH", envp[++i], 4) != 0)
		;
	path_f = ft_split(envp[i] + 5, ':');
	i = -1;
	// while (path_f[++i])
	// 	path_j[i] = ft_strjoin(path_f[i], cmd_i[0]);
	// i = -1;
	while (path_f[++i])
		printf("%s\n", path_f[i]);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// int i;

	// i = -1;
	// while(envp[++i]){
	// 	printf("i = %d\n", i);
	// 	printf("main = %s\n", envp[i]);
	// }
	printf("%s\n",ft_join_path("hello", "hello2"));
	// ft_set_path(&argv[2], envp);
	return (0);
}