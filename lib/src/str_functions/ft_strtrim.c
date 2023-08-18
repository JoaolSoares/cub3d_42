/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:46:34 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:02:16 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static size_t	ft_findstart(char const *s, char const *set)
{
	size_t	start;
	size_t	i;

	start = 0;
	while (s[start])
	{
		i = 0;
		while (s[start] != set[i] && set[i])
			++i;
		if (i != ft_strlen(set))
			++start;
		else
			break ;
	}
	return (start);
}

static size_t	ft_findend(char const *s, char const *set, size_t start)
{
	size_t	end;
	size_t	i;

	end = ft_strlen(s);
	while (end > start)
	{
		i = 0;
		while (s[end - 1] != set[i] && set[i])
			++i;
		if (i != ft_strlen(set))
			--end;
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_findstart(s1, set);
	end = ft_findend(s1, set, start);
	str = ft_substr(s1, start, end - start);
	return (str);
}

/* #include <stdio.h>
int main(void)
{
	char *s1 = "	 C 135,206,235 	 \n";
	char *set = "\t ";
	printf("  s1: %s\n  set: %s\ntrim:\n|%s|\n", s1, set, ft_strtrim(s1, set));
	char **temp = ft_split(ft_strtrim(s1, set), ' ', 1);
	ft_printf("trim = |%s|\n", temp[0]);
	ft_printf("trim = |%s|\n", temp[1]);
	ft_printf("trim = |%s|\n", temp[2]);
	ft_printf("-------------------\n");
	return 0;
}
 */