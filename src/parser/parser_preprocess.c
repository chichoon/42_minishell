/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_preprocess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/10/12 21:48:32 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void is_spaced(const char *input, int input_idx, int *flag)
{
	int prflag;
	
	prflag = is_pipe_redirection(input, input_idx);
	if (prflag > 0 && input_idx == 0)
	{
		if (input[input_idx + (prflag / 4) + 1] != ' ')
			*flag = 2;
	}
	else if (prflag > 0)
	{
		if (input[input_idx - 1] != ' ')
			*flag = 1;
		if (input[input_idx + (prflag / 4) + 1] != ' ')
			*flag = 2;
		if (input[input_idx - 1] != ' ' && input[input_idx + (prflag / 4) + 1] != ' ')
			*flag = 3;
	}
	else
		*flag = 0;
}

char *get_buf_considered(const char *input)
{
	int ix;
	int len;
	int qflag;
	int sflag;
	char *ret;

	ix = 0;
	len = 0;
	while (input[ix])
	{
		is_quoted(input[ix], &qflag);
		if (qflag == 0)
		{
			is_spaced(input, ix, &sflag);
			if (sflag)
				len = len + (sflag / 3 + 1);
		}
		len++;
		ix++;
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	return (ret);
}

void insert_space(char *buf, char input, int *buf_idx, int *sflag)
{
	if (*sflag == 3)
	{
		buf[(*buf_idx)++] = ' ';
		buf[(*buf_idx)++] = input;
		buf[(*buf_idx)++] = ' ';
	}
	if (*sflag == 1)
	{
		buf[(*buf_idx)++] = ' ';
		buf[(*buf_idx)++] = input;				
	}
	else if (*sflag == 2)
	{
		buf[(*buf_idx)++] = input;				
		buf[(*buf_idx)++] = ' ';
	}
}

int	preprocess_input(const char *input, char *buf)
{
	int		ix;
	int		jx;
	int		sflag;
	int		qflag;
	if (is_closed(input))
		return (ERROR_OCCURED);
	ix = 0;
	jx = 0;
	buf = get_buf_considered(input);
	while (input[ix])
	{
		is_inquote(input[ix], &qflag);
		is_spaced(input, ix, &sflag);
		if (sflag && !qflag)
			insert_space(buf, input[ix], &jx, &sflag);
		else
			buf[jx++] = input[ix];
		ix++;
	}
	buf[jx] = '\0';
	trs(buf);
	return (0);
}
