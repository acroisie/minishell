/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:27:49 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/13 17:39:56 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	detect_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static	int	word_count(const char *str, char sep)
{
	int	i;
	int	count;
	int	str_len;

	i = 1;
	count = 0;
	str_len = ft_strlen(str);
	while (i <= str_len)
	{
		if (!detect_sep(str[i - 1], sep) && (detect_sep(str[i], sep)
				|| str[i] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**fill_tab(const char *str, char **tab, char sep)
{
	int		start;
	int		end;
	int		i;
	int		j;

	start = 0;
	i = 0;
	while (i < word_count(str, sep))
	{
		j = 0;
		while (detect_sep(str[start], sep))
			start++;
		end = start;
		while (!detect_sep(str[end], sep) && str[end] != '\0')
			end++;
		tab[i] = ft_gc_calloc((end - start + 1), sizeof(char));
		if (tab[i] == NULL)
			return (0);
		while (start < end)
			tab[i][j++] = str[start++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word_nb;

	if (!s)
		return (NULL);
	word_nb = word_count(s, c);
	tab = ft_gc_calloc((word_nb + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(s, tab, c);
	return (tab);
}
