/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:11:01 by acroisie          #+#    #+#             */
/*   Updated: 2021/11/15 09:25:36 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*fill_str(const char *s1, int start, int end, int len_to_sub)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc((end - len_to_sub + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (start < end)
	{
		new_str[i] = s1[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		len_to_sub;
	int		start;
	char	*new_str;

	if (!s1 || !set)
		return (NULL);
	len_to_sub = 0;
	end = ft_strlen(s1);
	while (c_in_set(s1[len_to_sub], set))
		len_to_sub++;
	if (len_to_sub == end)
		return (ft_calloc(1, sizeof(char)));
	start = len_to_sub;
	while (c_in_set(s1[end - 1], set))
		end--;
	new_str = fill_str(s1, start, end, len_to_sub);
	return (new_str);
}
