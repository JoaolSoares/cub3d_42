/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemtx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:07:37 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/21 19:09:59 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_freemtx(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}