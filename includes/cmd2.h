/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 19:39:33 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD2_H
# define CMD2_H

# include "minishell.h"

typedef struct s_pipe_arr
{
	char	**cmd;
	char	**flags;
	char	**str;
	char	**envp;
	int		idx_max;
	int		fd_tmp;
	int		redir_flag;
	int		fildes_opened;
}	t_pipe_arr;

# define PIPE_READ 0
# define PIPE_WRITE 1
# define LLMAX 9223372036854775807
# define REDIR_NONE 0
# define REDIR_RIGHT_ONE 1
# define REDIR_RIGHT_TWO 2

/*
	* Pipelines
*/
void		minishell_pipe(char *cmd[], char *flag[], char *str[], char *envp[], int redir_flag);
char		*pipe_getcmd(char *cmd, char *envp[]);
void		ft_free_char2d(char **arr);

/*
	* Export
*/
# define	EXPORT_ERRID "\': not a valid identifier"
int			minishell_export(t_data *data);
char		*export_equal_check(char *str);
int			export_name_check(char *str, char *ptr_equal);
int			export_printerr(char *str);

/*
	* Exit
*/
# define	EXIT_ERRNUM ": numeric argument required\n"
void		minishell_exit(t_data *data);
void		exit_perror(char *input);
/*
	* Utilities
*/
char		*trim_quote(char *str);
char		*ft_strndup(char *str, int length);
char		*get_envname(char *str);
t_envlst	*find_env(char *envname, t_data *data);
int			minishell_perror(char *cmd, int err, int exit_status);
int			minishell_error(char *cmd, char *str, int exit_status);

#endif
