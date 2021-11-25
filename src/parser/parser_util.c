/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:37:34 by jekim             #+#    #+#             */
/*   Updated: 2021/11/26 04:06:34 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_pipe_redirection(const char *str, int ix, int str_l)
{
	if (str[ix] == '|')
		return (1);
	if (str[ix] == '>')
	{
		if (ix < str_l - 1 && str[ix + 1] == '>')
			return (2);
		return (1);
	}
	if (str[ix] == '<')
	{
		if (ix < str_l - 1 && str[ix + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

int is_quotation(const char *str, int ix)
{
	return (is_double_quote(str, ix) || is_single_quote(str, ix));
}

int	is_double_quote(const char *str, int ix)
{
	return ((int)str[ix] == 34);
}

int	is_single_quote(const char *str, int ix)
{
	return ((int)str[ix] == 39);
}

void	is_inquoted(const char *str, int ix, int *flag)
{
	if (is_double_quote(str, ix))
	{
		if (*flag == 2)
			*flag = 0;
		else if (*flag == 0)
			*flag = 2;
	}
	if (is_single_quote(str, ix))
	{
		if (*flag == 1)
			*flag = 0;
		else if (*flag == 0)
			*flag = 1;
	}
}
