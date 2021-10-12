/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:24:06 by jekim             #+#    #+#             */
/*   Updated: 2021/10/12 17:10:52 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

//지우시오!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}
//지우시오!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void	exit_perror(char *input)
{
	write(1, "exit: ", 6);
	write(1, input, ft_strlen(input));
	write(1, ": numeric argument required\n", 29);
}

long long	is_overflow_ll(char *str)
{
	unsigned long long	converted;
	int					minus;

	converted = 0;
	minus = 1;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str <= '9' && *str >= '0')
		converted = converted * 10 + (*str++ - '0');
	if (converted > 9223372036854775807 && minus == 1)
		return (-1);
	if (converted - 1 > 9223372036854775807 && minus == -1)
		return (-1);
	return (converted % 256);
}

static int	is_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str > '9' || *str < '0')
			return (0);
		str++;
	}
	return (1);
}

//void	exit_withargs(t_token *tree)
void	exit_withargs(char *str)
{
	long long	errno_converted;

	if ((ft_strlen(str) > 20) || (ft_strlen(str) > 19 && *str != '-'))
		exit_perror(str);
	else
	{
        errno_converted = is_overflow_ll(str);
		if (errno_converted < 0)
			exit_perror(str);
		else
		{
			write(1, "exit\n", 5);
		}
	}
	exit(errno_converted);
}

//longlong 체크용~
int main(void)
{
	char *str = "9223372036854775808";
	exit_withargs(str);
}
