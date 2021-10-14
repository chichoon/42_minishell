/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipepipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:04:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/14 18:46:12 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	count_cmd(char *cmd[])
{
	int	length;

	length = 0;
	while (cmd[length])
		length++;
	return (length);
}

t_pipe_arr	*pipe_struct(char *cmd[], char *flags[], char *str[], char *envp[])
{
	t_pipe_arr	*struct_pipe;

	struct_pipe = malloc(sizeof(t_pipe_arr));
	if (!struct_pipe)
		return (0);
	struct_pipe->cmd = cmd;
	struct_pipe->flags = flags;
	struct_pipe->str = str;
	struct_pipe->envp = envp;
	struct_pipe->idx_max = count_cmd(cmd);
	struct_pipe->fd_tmp = STDIN_FILENO;
	return (struct_pipe);
}

void	pipe_child(t_pipe_arr *struct_pipe, int fd_in, int fd_out, int idx)
{
	char	*cmd_path;
	char	*exec_argv[4]; //이거는 나중에 수정하기 !!!!!!!!!!

	if (dup2(fd_in, STDIN_FILENO) < 0)
		exit(minishell_perror("pipe: ", -1, 1));
	if (idx + 1 < struct_pipe->idx_max)
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			exit(minishell_perror("pipe: ", -1, 1));
	close(fd_out);
	close(fd_in);
	cmd_path = pipe_getcmd(struct_pipe->cmd[idx], struct_pipe->envp);
	if (!cmd_path)
		exit(minishell_perror("pipe: ", 2, 1));
	exec_argv[0] = cmd_path;
	exec_argv[1] = struct_pipe->flags[idx];
	if (count_cmd(struct_pipe->str) > idx)
	{
		exec_argv[2] = struct_pipe->str[idx];
		exec_argv[3] = 0;
	}
	else
		exec_argv[2] = 0;
	execve(cmd_path, exec_argv, struct_pipe->envp);
	exit(minishell_perror("pipe: ", -1, 1));
}

int	pipe_makepipe(t_pipe_arr *struct_pipe, int idx)
{
	int	fd[2];
	int	pipe_pid;

	if (idx + 1 < count_cmd(struct_pipe->cmd))
		if (pipe(fd) < 0)
			return (-1);
	pipe_pid = fork();
	if (!pipe_pid)
	{
		pipe_child(struct_pipe, struct_pipe->fd_tmp, fd[PIPE_WRITE], idx);
	}
	else if (pipe_pid < 0)
		exit(minishell_perror("pipe: ", -1, 1));
	else
	{
		if (struct_pipe->fd_tmp != STDIN_FILENO)
			close(struct_pipe->fd_tmp);
		struct_pipe->fd_tmp = fd[PIPE_READ];
		close(fd[PIPE_WRITE]);
	}
	return (pipe_pid);
}

void	minishell_pipe(char *cmd[], char *flag[], char *str[], char *envp[])
{
	t_pipe_arr	*struct_pipe;
	int			cmd_len;
	int			idx;
	int			wait_return;
	int			status;
	int			status_save;
	int			last_pid;

	if (!cmd)
		return ;
	struct_pipe = pipe_struct(cmd, flag, str, envp);
	if (!struct_pipe)
		return ;
	cmd_len = count_cmd(cmd);
	idx = -1;
	while (++idx < cmd_len)
	{
		last_pid = pipe_makepipe(struct_pipe, idx);
		if (last_pid < 0)
		{
			minishell_perror("pipe: ", -1, 1);
			return ;
		}
	}
	while (1)
	{
		wait_return = wait(&status);
		if (wait_return == last_pid)
			status_save = status;
		if (wait_return == -1)
			return ;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char *cmd[] = {"ls", "cat", "cat", "cat", "cat", "head", 0};
	char *flag[] = {"-al", "-e", "-e", "-e", "/dev/urandom", "-10", 0};
	char *str[] = {0};

	minishell_pipe(cmd, flag, str, envp);
	//cat -e pipepipe.c | cat -e | cat -e | cat -e | cat -e
}
