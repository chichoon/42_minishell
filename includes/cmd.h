/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 16:49:31 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

typedef enum s_state
{
	CMD = 0,
	FLAG,
	PIPE,
	REDIRECT,
	FILEPATH,
	STR
}	t_state;

typedef struct s_token
{
	char			*content;
	int				ix;
	t_state			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum s_env_state
{
	ENV = 0,
	EXPORT_ONLY,
	TEMP_ENV,
}	t_env_state;

typedef struct s_envlst
{
	char			*key;
	char			*value;
	t_env_state		env_state;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_data
{
	t_envlst		*envlst;
	t_token			*input;
	t_input_process	*ip;
	int				dq;
	void			**malloc_queue;
	char			*homedir;
}	t_data;

typedef struct s_pipe
{
	char	**envp;
	int		index;
	int		max_index;
	int		fd_tmp;
	int		last_pid;
}	t_pipe;

# define PIPE_READ 0
# define PIPE_WRITE 1
# define LLMAX 9223372036854775807
# define REDIR_NONE 0
# define REDIR_RIGHT_ONE 1
# define REDIR_RIGHT_TWO 2

/*
	* Minishell Executor
*/
# define	EXEC_ERRNODIR ": No such file or directory"
# define	EXEC_ERRDIR ": is a directory"
# define	EXEC_ERRNOCMD ": command not found"
# define	EXEC_ERRPARSE ": failed to parse arguments"
# define	EXEC_ERRFORK "failed to make process"
# define	EXEC_NOTBUILTIN -424242
# define	EXEC_ISDIR 1
# define	EXEC_ISFILE 0
# define	EXEC_NOTFILE -1
int			exec_builtin(t_data *data, t_token *input);
int			exec_program(t_data *data, t_token *input, char *envp[]);
char		*exec_getcmd(char *cmd, char *envp[]);
void		exec_dup_iofd(t_token *input);
char		*if_file(char *cmd);
int			cmd_access(char *path);

/*
	* Pipelines
*/
# define	PIPE_ERR "failed to make PIPE / REDIRECTION"
int			minishell_pipe(t_data *data, char *envp[]);
t_pipe		*pipe_struct(t_token *input, char *envp[]);
char		**pipe_insert_arr(t_token *input, char *cmd_path);

/*
	* cd & pwd & echo
*/
# define	CD_ERRNODIR ": No such file or directory"
# define	CD_ERROPT ": invalid option\ncd : usage: cd [dir]"
# define	CD_ERROLD "OLDPWD not set"
# define	CD_ERRHOME "HOME not set"
# define	PWD_ERROPT ": invalid option\npwd: usage: pwd"
# define	PWD_ERRFAIL "failed to get current working directory"
# define	CD_PWDNOTSET -42
# define	CD_HOMENOTSET -4242
# define	CD_FAILED -1
# define	CD_SUCCESS 0
int			minishell_cd(t_data *data, t_token *input);
int			minishell_pwd(t_token *input);
int			minishell_echo(t_token *input);

/*
	* Export
*/
# define	EXPORT_ERRID ": not a valid identifier"
# define	EXPORT_ERROPT ": invalid option\n\
export: usage: export [name[=value] ...]"
int			minishell_export(t_data *data, t_token *input);

/*
	* Env
*/
# define	ENV_ERROPT ": illegal option\nusage: env"
int			minishell_env(t_data *data, t_token *input);

/*
	* Unset
*/
# define	UNSET_ERRID ": not a valid identifier"
# define	UNSET_ERROPT ": invalid option\n\
unset: usage: unset [name ...]"
int			minishell_unset(t_data *data, t_token *input);

/*
	* Exit
*/
# define	EXIT_ERRNUM ": numeric argument required"
# define	EXIT_ERRMANY "too many arguments"
int			minishell_exit(t_data *data, t_token *input);

/*
	* Redirection
*/
int			get_redir_ofd(t_token *input);
int			get_redir_ifd(t_token *input);

/*
	* Environment Variables
*/
t_envlst	*find_env(char *envname, t_data *data);
char		*get_env(char *envname, t_data *data);
int			env_name_check(char *str, char *ptr_equal);
char		*env_equal_check(char *str);
int			save_env(
				t_data *data,
				char *env_key,
				char *env_value,
				t_env_state flag);

/*
	* Utilities
*/
# define	SHELL_ERRALLOC "failed to allocate memory"
int			builtin_error(char *cmd, char *error_str, int dollar_q);
int			check_flag(t_token *input);
int			free_token(t_token *input, int return_status);
void		ft_free_char2d(char **arr);

#endif
