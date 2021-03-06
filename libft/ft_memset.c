/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 10:54:14 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/21 10:54:16 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char *tmp;

	tmp = (char*)b;
	while (len > 0)
	{
		*tmp = c;
		tmp++;
		len--;
	}
	return (b);
}
