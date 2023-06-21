/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:00:14 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/20 21:53:45 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_deletechar(char *str, size_t index)
{
	char	*temp;
	char	*ret;

	if (index > ft_strlen(str) + 1)
		return (NULL);
	temp = ft_strdup(str);
	free(str);
	while (temp[index + 1])
	{
		temp[index] = temp[index + 1];
		index++;
	}
	ret = ft_strdup_until(temp, ft_strlen(temp) - 1);
	free(temp);
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *str = ft_strdup("hello 'world");
// 	char *temp = ft_strdup(str);
// 	free(str);
// 	str = ft_deletechar(temp, 6);
// 	printf("%s\n", str);
// 	free(str);

// 	return 0;
// }