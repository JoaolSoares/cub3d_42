/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:39:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:02:01 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_instr(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

static char	*ft_wordcreate(char *dest, char const *s, int index, int len)
{
	int		j;

	j = 0;
	while (len > 0)
	{
		dest[j] = s[index - len];
		++j;
		--len;
	}
	dest[j] = 0;
	return (dest);
}

static char
	**ft_splitwords(char **split, char const *s, char *set, int words_count)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (s[i] && j < words_count)
	{
		len = 0;
		while (s[i] && ft_instr(s[i], set))
			++i;
		while (s[i] && !ft_instr(s[i], set))
		{
			++i;
			++len;
		}
		split[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!split[j])
			return (0);
		ft_wordcreate(split[j], s, i, len);
		++j;
	}
	split[j] = 0;
	return (split);
}

static int	ft_wordscount(char const *s, char *set)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && !ft_instr(s[i], set))
			++count;
		else if (!ft_instr(s[i], set) && ft_instr(s[i - 1], set))
			++count;
		++i;
	}
	return (count);
}

char	**ft_mult_split(char *s, char *set, int opt)
{
	char	**split;
	int		words_count;

	if (!s || !set)
		return (0);
	words_count = ft_wordscount(s, set);
	split = (char **)malloc(sizeof(s) * (words_count + 1));
	if (!split)
		return (0);
	ft_splitwords(split, s, set, words_count);
	if (opt == 1)
		free(s);
	return (split);
}

/* #include <stdio.h>
int main(void)
{
	char *str = "	 C 123		, 123	,  123    "; 
	char *set = "\t ,";
	
	char **array = ft_mult_split(str, set, 0);
	
	
	int i = -1;
	while (++i <= ft_wordscount(str, set))
		ft_printf("array[%i] = %s\n", i, array[i]);
	
	i = -1;
	while (++i <= ft_wordscount(str, set))
		free(array[i]);
	free(array);

	return 0;
} */
