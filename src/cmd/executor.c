/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:39:47 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/28 15:17:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"
/*
static int	exec_if_pipe(t_data *data)
{
	t_token	*input;

	input = data->input;
	while (input)
	{
		if (input->type == PIPE)
			return (1);
		input = input->next;
	}
	return (0);
}
*/
int	exec_builtin(t_data *data, t_token *input)
{
	/*
	if (ft_strequel(input->content, "cd"))
		return (minishell_cd(data));
	else if (ft_strequel(input->content, "echo"))
		return (minishell_echo(data));
	else if (ft_strequel(input->content, "env"))
		return (minishell_env(data));
	else if (ft_strequel(input->content, "exit"))
		return (minishell_exit(data));
	else if (ft_strequel(input->content, "export"))
		return (minishell_export(data));
	else if (ft_strequel(input->content, "unset"))
		return (minishell_unset(data));
	else if (ft_strequel(input->content, "pwd"))
		return (minishell_pwd(data));
	else
		return (EXEC_NOTBUILTIN);
	*/
	(void)data;
	(void)input;
	return (EXEC_NOTBUILTIN);
}

int	exec_program(t_token *input, char *envp[])
{
	char	*cmd_path;
	char	**exec_argv;

	cmd_path = getcmd(input->content, envp);
	if (!cmd_path)
		exit(builtin_error(
				"shell", ft_strjoin(input->content, EXEC_ERRNOCMD), 127));
	exec_argv = pipe_insert_arr(input, cmd_path);
	if (!exec_argv)
		exit(builtin_error(
				"shell", ft_strjoin(input->content, EXEC_ERRPARSE), 1));
	execve(cmd_path, exec_argv, envp);
	ft_free_char2d(exec_argv);
	free(cmd_path);
	exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
}
/*
int	executor(t_data *data, char *envp[])
{
	t_token	*input;

	input = data->input;
	if (exec_if_pipe(data))
		minishell_pipe(data, envp);
	else if (exec_builtin(data, input) == EXEC_NOTBUILTIN))

}
*/
