/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:30:17 by jekim             #+#    #+#             */
/*   Updated: 2021/10/09 21:48:53 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_envfile(char **envp)
{
	int	ix;
	int	len;
	int	fd;
	int	write_checker;

	ix = -1;
	len = 0;
	fd = open("./envrc", O_WRONLY, S_IWUSR | S_IRUSR);
	while (envp[++ix])
	{
		len = ft_strlen(envp[ix]);
		write_checker = write(fd, envp[ix], len);
		write(fd, "\n", 1);
	}
	close(fd);
}

static t_envlst	*create_node_envlst(char *env_line)
{
	int			len;
	int			equel_idx;
	t_envlst	*tmp;

	tmp = (t_envlst *)ft_calloc(sizeof(t_envlst), 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	len = ft_strlen(env_line);
	equel_idx = indexOf_char(env_line, '=');
	tmp->key = ft_substr(env_line, 0, equel_idx);
	tmp->value = ft_substr(env_line, equel_idx + 1, len - equel_idx);
	return (tmp);
}

static int	set_envlst(char **envp, int fd, t_data *data)
{
	int			ix;
	char		*buf;
	t_envlst	*nptr;

	ix = -1;
	nptr = data->envlst;
	printf("pointer:  %p\n", nptr);
	if (fd == -1)
		fd = open("./envrc", O_RDONLY, S_IWUSR | S_IRUSR);
	while (envp[++ix])
	{
		ft_strgnl(fd, &buf);
		nptr = create_node_envlst(buf);
		printf("pointer:  %p\n", nptr);
		free(buf);
		if (envp[ix + 1] != NULL)
			nptr = nptr->next;
	}
	nptr->next = NULL;
	nptr = data->envlst;
	printf("pointer:  %p\n", nptr);
	while (nptr != NULL)
	{
		printf("%s=%s\n", nptr->key, nptr->value);
		nptr = nptr->next;
	}
	return (0);
}

int	init_env(char **envp, t_data *data)
{
	int	envfd;

	envfd = open("./envrc", O_RDONLY | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR);
	if (envfd != -1)
		set_envfile(envp);
	set_envlst(envp, envfd, data);
	return (0);
}