/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:33:08 by mkong             #+#    #+#             */
/*   Updated: 2024/01/23 14:58:12 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_t_d(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != 0)
		free(cmd[i]);
	free(cmd);
}

static void	free_info(t_info *info)
{
	free_t_d(info->path);
	free(info->infile);
	free(info->outfile);
	free(info);
	if (close(info->fds[0]) == -1 || close(info->fds[1]) == -1)
		error_exit();
}

static char	**make_cmd(char *av)
{
	char	**cmd;
	char	sep;
	int		i;

	sep = ' ';
	i = 0;
	if (ft_strchr(av, '\''))
		sep = '\'';
	else if (ft_strchr(av, '\"'))
		sep = '\"';
	if (sep != ' ')
	{
		cmd = (char **)malloc(sizeof(char *) * 3);
		cmd[i++] = ft_strndup(av, ft_strchr(av, ' ') - av);
		cmd[i++] = ft_strndup(ft_strchr(av, sep) + 1, ft_strrchr(av, sep)
				- ft_strchr(av, sep) - 1);
		cmd[i] = NULL;
	}
	else
		cmd = ft_split(av, sep);
	return (cmd);
}

int	main(int ac, char *av[], char *envp[])
{
	t_info	*info;
	char	*cmd_path;
	int		i;

	if (ac < 5)
		exit(1);
	info = info_initialize(ac, av, envp);
	i = 1;
	while (++i < ac - 1)
	{
		info->cmd = make_cmd(av[i]);
		cmd_path = find_path(info);
		if (info->cmd == 0 || cmd_path == 0)
			error_exit();
		if (i == 2)
			exec_first(info, cmd_path, envp);
		else if (i == ac - 2)
			exec_last(info, cmd_path, envp);
		else
			exec_mid(info, cmd_path, envp);
		free_t_d(info->cmd);
		free(cmd_path);
	}
	free_info(info);
	return (0);
}