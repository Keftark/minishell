/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:52:05 by cpothin           #+#    #+#             */
/*   Updated: 2023/09/13 08:55:38 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	LIBRARY: string.h

	SYNOPSIS: 	Compare two string s1 and s2 and return the ASCII
				difference.
*/
#include "../../inc/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((s1 && !s2) || (!s1 && s2))
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
