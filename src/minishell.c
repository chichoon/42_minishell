/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/13 22:27:52 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_STDIN_input(char *input, t_data *data)
{
	parse_input_string(input, data);
	add_history(input);
	if (data->input && data->input->next)
	{
		minishell_executor(data);
		free_token(data->input);
	}
}

void handle_EOF_NO_STDIN(void)
{
	write(0, "\bexit\n", 6);
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
	while (1)
	{
		set_signal_handler_default();
		input = readline(PROMPT);
		if (input)
			handle_STDIN_input(input, &data);
		else
			handle_EOF_NO_STDIN();
		free(input);
	}
	return (0);
}
