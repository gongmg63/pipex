/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:47 by mkong             #+#    #+#             */
/*   Updated: 2024/01/26 14:15:30 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first(t_info *info)
{
	int	fd;

	fd = 0;
	check_fail(pipe(info->fds));
	info->child++;
	info->pid = fork();
	check_fail(info->pid);
	if (info->pid == 0)
	{
		fd = open(info->infile, O_RDONLY);
		check_fail(fd);
		if (ft_strncmp(info->cmd_path, "CnF", 3) == 0)
			error_exit("command not found");
		check_fail(close(info->fds[0]));
		check_fail(dup2(fd, 0));
		check_fail(close(fd));
		check_fail(dup2(info->fds[1], 1));
		check_fail(close(info->fds[1]));
		check_fail(execve(info->cmd_path, info->cmd, info->envp));
	}
	check_fail(close(fd));
}

void	exec_last(t_info *info)
{
	int	fd;

	fd = 0;
	info->child++;
	info->pid = fork();
	check_fail(info->pid);
	if (info->pid == 0)
	{
		fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check_fail(fd);
		if (ft_strncmp(info->cmd_path, "CnF", 3) == 0)
			error_exit("command not found");
		check_fail(close(info->fds[1]));
		check_fail(dup2(fd, 1));
		check_fail(close(fd));
		check_fail(dup2(info->fds[0], 0));
		check_fail(close(info->fds[0]));
		check_fail(execve(info->cmd_path, info->cmd, info->envp));
	}
	check_fail(close(info->fds[0]));
	check_fail(close(info->fds[1]));
}
