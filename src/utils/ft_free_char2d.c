/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:44:15 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 11:44:25 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

void	ft_free_char2d(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}
