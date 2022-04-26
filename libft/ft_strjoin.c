/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:07:24 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/25 18:17:00 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_gc_strdup((char *)s2));
	if (!s2)
		return (ft_gc_strdup((char *)s1));
	str = ft_gc_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	**ft_addline(char **src1, char *s2)
{
	int		i;
	int		j;
	char	**dest = NULL;

	i = 0;
	j = 0;
	dest = ft_gc_calloc((ft_destlen(src1) + 2), sizeof(char *));
	if (dest == NULL)
		return (NULL);
	while (src1[i])
	{
		dest[i] = ft_gc_strdup(src1[i]);
		// dprintf(2, "Dest: %s\n", dest[i]); // to delete
		i++;
	}
	j = 0;
	dest[i] = ft_gc_strdup(s2);
	dest[i + 1] = NULL;
	// // dest[ft_destlen(dest)] = NULL;
	// dprintf(2, "Destend: %s\n", dest[i]); // to delete
	// dprintf(2, "Destend 0: %s\n", dest[i + 1]); // to delete
	ft_free_split(src1);
	ft_gc_free(s2);
	return (dest);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_gc_strdup(s2));
	if (!s2)
		return (ft_gc_strdup(s1));
	str = ft_gc_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	ft_gc_free(s1);
	return (str);
}

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_gc_strdup(s2));
	if (!s2)
		return (ft_gc_strdup(s1));
	str = ft_gc_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	ft_gc_free(s2);
	return (str);
}
