/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:00:59 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 14:28:47 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd2(t_minishell *data, int i, int j, char **cmd_args)
{
	char		**home;
	struct stat	s;

	home = ft_split(data->new_env[j], '=');
	stat(cmd_args[1], &s);
	if (S_ISREG(s.st_mode))
		return (return_error_builtin("cd: ", cmd_args[1],
				": Not a directory", 1));
	if (access(cmd_args[1], X_OK) == -1 && access(cmd_args[1], F_OK) == 0)
		return (return_error_builtin("cd: ", cmd_args[1],
				": Permision denied", 1));
	else if (cmd_args[1])
	{
		if (chdir(cmd_args[1]) == -1)
			return (return_error_builtin("cd: ", cmd_args[1],
					": No such file or directory", 1));
	}
	else if (!cmd_args[1])
		chdir(home[1]);
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[i] = ft_strjoin_free_s2("PWD=", data->cd_pwd);
}

void	ft_cd(t_minishell *data, char **cmd_args, t_lst_cmd *lst_cmd)
{
	int		i;
	int		j;
	int		k;

	i = find_in_env(data, "PWD");
	k = find_in_env(data, "OLDPWD");
	j = find_in_env(data, "HOME");
	if (j == ft_destlen(data->new_env) && !cmd_args[1])
		return (return_error_builtin("cd: ", "HOME", " not set", 1));
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	oldpwd(data);
	ft_cd2(data, i, j, cmd_args);
	if (lst_cmd->next || lst_cmd->prev)
		exit(0);
}
