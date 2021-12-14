/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/14 20:57:42 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_STDIN_input(char *input, t_data *data)
{
	int err_checker;

	err_checker = parse_input_string(input, data);
	add_history(input);
	if (data->input && data->input->next && err_checker != ERROR_OCCURED)
	{
		minishell_executor(data);
		free_token(data->input);
	}
}

void handle_EOF_NO_STDIN(void)
{
	write(0, "exit\n", 5);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	if (print_intro(argc, argv)
		|| init_env(envp, &data))
		exit(EXIT_FAILURE);
	add_shlvl(&data);
	kill(0, SIGUSR1);
	while (1)
	{
		set_signal_handler_default();
		signal(SIGUSR1, set_signal_handler_ignore);
		input = readline(PROMPT);
		if (input)
			handle_STDIN_input(input, &data);
		else
			handle_EOF_NO_STDIN();
		free(input);
	}
	return (0);
}
