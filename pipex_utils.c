/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:07:20 by psuanpro          #+#    #+#             */
/*   Updated: 2022/08/04 23:42:45 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlcpy_split(char *dst, char const *src, size_t dstsize, char *cmd)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (dstsize <= 0)
		return (ft_strlen(src));
	while (++i < dstsize - 1 && src[i])
		dst[i] = src[i];
	dst[i++] = '/';
	j = -1;
	while (cmd[++j])
		dst[i + j] = cmd[j];
	dst[i + j] = '\0';
	return (ft_strlen(src));
}

static	size_t	ft_countword(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (*s != '\0' && *s != c)
		j += 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			j += 1;
		i++;
	}
	return (j + 1);
}

static	size_t	ft_countcword(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] == c)
		i++;
	while (i < len && s[i])
	{
		if (s[i] == c)
		{
			i++;
			break ;
		}
		i++;
		j++;
	}
	return (j + 1);
}

static	char	*ft_getword(char const *s, char c, char *cmd)
{
	char	*str;
	str = malloc(sizeof(char) * ft_countcword(s, c) + 3 + ft_strlen(cmd));
	while (*s == c)
	{
		s++;
	}
	ft_strlcpy_split(str, s, ft_countcword(s, c), cmd);
	return (str);
}

char	**ft_split_join(char const *s, char c, char *cmd)
{
	char	**array;
	int		i;
	int		sl;

	i = -1;
	if (!s)
		return (NULL);
	sl = ft_countword(s, c);
	array = (char **)malloc(ft_countword(s, c) * (sizeof(char *)));
	if (!array)
		return (NULL);
	while (++i < sl - 1)
	{
		while (*s == c)
			s++;
		array[i] = ft_getword(s, c, cmd);
		s += ft_countcword(s, c);
	}
	array[i] = NULL;
	return (array);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;

// 	char **ret;
// 	int i= -1;
// 	// while (envp[++i])
// 	// 	printf("%s\n", envp[3);

// 	ret = ft_split_join(envp[3]+ 5, ':',  "ls");

// 	while (ret[++i])
// 		printf("%s\n", ret[i]);
// }