/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/14 20:32:06 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD2_H
# define CMD2_H

# include "minishell.h"

# define REDIR_NONE		0;
# define REDIR_SINGLE	1;
# define REDIR_DOUBLE	2;

typedef struct s_pipe_arr
{
	char	**cmd;
	char	**flags;
	char	**str;
	char	**envp;
	int		idx_max;
	int		fd_tmp;
}	t_pipe_arr;

# define PIPE_READ 0
# define PIPE_WRITE 1

/*
	* Pipelines
*/
char		*pipe_getcmd(char *cmd, char *envp[]);
void		ft_free_char2d(char **arr);

/*
	* Environment Variables
*/
char		*get_envname(char *str);
t_envlst	*find_env(char *envname, t_data *data);

/*
	* Exit
*/
int			minishell_perror(char *cmd, int err, int exit_status);

#endif
