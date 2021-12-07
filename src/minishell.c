/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/07 19:09:03 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	if (print_intro(argc, argv)
		|| init_env(envp, &data)
		|| set_signal_handler())
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline(PROMPT);
		if (input)
		{
			trs(input);
			parse_input_string(input, &data);
			add_history(input);
			if (data.input && data.input->next)
				minishell_executor(&data, envp);
		}
		free(input);
	}
	return (0);
}
