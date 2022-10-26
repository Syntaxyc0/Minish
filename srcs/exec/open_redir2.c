/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:21:50 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 17:04:11 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*already_exist(t_redir *redir)
{
	char	*ret;
	
	ret = ft_strdup(redir->filename);
	while (access(ret, R_OK) == 0)
	{
		ret = ft_strjoin_free(ret, "0", 1, 0);
	}
	return (ret);
}

void	heredoc_anihilator(t_mini *mini)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = mini->commands;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (cmd->redir->type == 5)
				if (unlink(redir->heredoc_name) == -1)
					return_perror(1, 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	ft_heredoc(t_command *cmd, t_redir *redir, t_mini *mini)
{
	int		fd;
	int		pid;

	if (cmd->fd[0])
		if (close(cmd->fd[0]) == -1)
			return_perror(1, -1);
	redir->heredoc_name = already_exist(redir);
	fd = open(redir->heredoc_name, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		return_perror(1, 0);
	process_sig_handle();
	pid = fork();
	if (pid == -1)
		exit_perror(1);
	if (pid == 0)
		heredoc_child(redir, mini, fd);
	close(fd);
	wait(&g_exit_status);
	g_exit_status /= 256;
	if (g_exit_status == 42)
	{
		printf("connard\n");
		ft_close_all(mini);
		return (-1);
	}
	cmd->fd[0] = open(redir->heredoc_name, O_CREAT | O_RDWR, 0666);
	if (cmd->fd[0] < 0)
		return_perror(1, 0);
	heredoc_iocondition(cmd);
	return (0);
}

void	heredoc_child(t_redir *redir, t_mini *mini, int fd)
{
	char *line;
	
	while (1)
	{
		heredoc_sig_handle();
		line = readline(">");
		if (g_exit_status == -1)
		{
			close(fd);
			//printf("here_document : wanted '%s'\n", redir->filename);
			printf("iccci\n");
			ft_close_all(mini);
			exit_free_status(mini, 42);
		}
		if (!ft_strncmp(redir->filename, line, str_big(redir->filename, line)))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	ft_close_all(mini);
	close(fd);
	exit_free_status(mini, 0);
}