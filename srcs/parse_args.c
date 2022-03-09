/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/09 16:57:21 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_quotes_clean(t_lst_cmd *lst_cmd)
// {
// 	int			i;
// 	int			j;
// 	t_lst_cmd	*start;

// 	start = lst_cmd;
// 	while (lst_cmd)
// 	{
// 		i = 0;
// 		while (lst_cmd->args[i])
// 		{
// 			j = 0;
// 			while (lst_cmd->args[i][j])
// 			{
// 				if (lst_cmd->args[i][j] == '"')
// 				{
// 					lst_cmd->args[i] = ft_memmove(&lst_cmd->args[i][j + 1], &lst_cmd->args[i][j], ft_strlen(lst_cmd->args[i] - 1));
// 					j++;
// 					while (lst_cmd->args[i][j] != '"')
// 						j++;
// 					lst_cmd->args[i] = ft_memmove(&lst_cmd->args[i][j + 1], &lst_cmd->args[i][j], ft_strlen(lst_cmd->args[i] - 1));
// 				}
// 				else if (lst_cmd->args[i][j] == '\'')
// 				{
// 					lst_cmd->args[i] = ft_memmove(&lst_cmd->args[i][j + 1], &lst_cmd->args[i][j], ft_strlen(lst_cmd->args[i] - 1));
// 					j++;
// 					while (lst_cmd->args[i][j] != '\'')
// 						j++;
// 					lst_cmd->args[i] = ft_memmove(&lst_cmd->args[i][j + 1], &lst_cmd->args[i][j], ft_strlen(lst_cmd->args[i] - 1));
// 				}
// 				j++;
// 			}
// 			i++;
// 		}
// 		lst_cmd = lst_cmd->next;
// 	}
// 	lst_cmd = start;
// }

void	ft_quotes_clean(t_lst_cmd *lst_cmd)
{
	int	i;
	int	j;
	int	n;
	char	tmp;

	while (lst_cmd)
	{
		i = 0;
		while (lst_cmd->args[i])
		{
			j = 0;
			n = 0;
			while (lst_cmd->args[i][j])
			{
				if (lst_cmd->args[i][j] == '"' || lst_cmd->args[i][j] == '\'')
				{
					tmp = lst_cmd->args[i][j];
					n++;
					while (lst_cmd->args[i][n] && lst_cmd->args[i][n] != tmp)
						lst_cmd->args[i][j++] = lst_cmd->args[i][n++];
					n++;
				}
				lst_cmd->args[i][j++] = lst_cmd->args[i][n++];
					//lst_cmd->args[i] = ft_memmove(&lst_cmd->args[i][j], &lst_cmd->args[i][j + n], ft_strlen(&lst_cmd->args[i][j + n]));		
			}
			lst_cmd->args[i][j++] = '\0';
			i++;
		}
		lst_cmd = lst_cmd->next;
	}
	
}


static int	detect_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static	int	args_count(const char *str, char sep)
{
	int	i;
	int	count;
	int	str_len;

	i = 0;
	count = 0;
	str_len = ft_strlen(str);
	while (i <= str_len)
	{
		if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\0')
					exit (1); //Add a clean exit with message: "Unclosed quotes"
			}
		}
		else if (str[i] == '\'')
		{
			while (str[++i] != '\'')
			{
				if (str[i] == '\0')
					exit (1); //Add a clean exit with message: "Unclosed quotes"
			}
		}
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
	while (i < args_count(str, sep))
	{
		j = 0;
		while (detect_sep(str[start], sep) || str[start] == ' ')
			start++;
		end = start;
		while (!detect_sep(str[end], sep) && str[end] != '\0')
		{
			if (str[end] == '"')
			{
				while (str[end] && str[++end] != '"')
					;
				// break ;
			}
			else if (str[end] == '\'')
			{
				while (str[end] && str[++end] != '\'')
					;
				// break ;
			}
			end++;
		}
		tab[i] = malloc((end - start + 1) * sizeof(char));
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

char	**ft_split_args(char const *s, char c)
{
	char	**tab;
	int		word_nb;

	if (!s)
		return (NULL);
	word_nb = args_count(s, c);
	tab = malloc((word_nb + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(s, tab, c);
	return (tab);
}

t_lst_cmd	*ft_parse_args(char *line)
{
	t_lst_cmd	*lst_cmd;
	char		**temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = ft_split_args(line, '|');
	lst_cmd = ft_create_cell(ft_split_args(temp[0], ' '), NULL);
	/* SOME MALLOC TO FREE AROUND THERE*/
	while (temp[i])
		i++;
	if (i > 0)
	{
		lst_cmd->args = ft_split_args(temp[j], ' ');
		j++;
		while (j < i)
		{
			ft_lstadd_cell(lst_cmd, ft_split_args(temp[j], ' '));
			j++;
		}
	}
	ft_quotes_clean(lst_cmd);
	return (lst_cmd);
}
