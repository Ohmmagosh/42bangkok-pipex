/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:58:38 by psuanpro          #+#    #+#             */
/*   Updated: 2022/07/21 03:47:13 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>


size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
//test function
void	ft_set_path(char **cmd, char **envp);
char	*ft_join_path(char const *s1, char const *s2);
#endif
