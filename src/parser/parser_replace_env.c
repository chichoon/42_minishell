/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/12/12 04:24:17 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** env part
*/
int is_start_charset_envkey(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int is_end_envkey(const char *src, int ix)
{
	if (ix == 0 && !is_start_charset_envkey(src[ix]))
		return (TRUE);
	if (!ft_isalnum(src[ix]) && src[ix] != '_')
		return (TRUE);
	return (FALSE);
}

int get_envkey_l(const char *src, int ix)
{
	int ret;

	ret = 0;
	while (src[ix])
	{
		if (is_end_envkey(src, ix) == TRUE)
			break ;
		ix++;
		ret++;
	}
	return (ret);
}

/*
** do not care here about get_env() returns NULL;
** when get_env() returns NULL, it means that the value was not found
*/
int search_and_copy_envval(const char *src, t_eb *eb, t_data *data)
{
	eb->key_l = get_envkey_l(src, eb->now_ix + 1);
	eb->envkey = ft_strndup((char *)(src + eb->now_ix + 1), eb->key_l);
	eb->envval = get_env(eb->envkey, data);
	eb->value_l = ft_strlen(eb->envval);
	return (0);
}

t_eb	*set_envbucket(char *src, int now_ix)
{
	t_eb	*ret;
	
	ret = (t_eb *)ft_calloc(sizeof(t_eb), 1);
	if (!ret)
		return (NULL);
	ret->now_ix = now_ix;
	ret->srcp = src;
	ret->src_l = ft_strlen(src);
	return (ret);
}

char	*return_append_env(t_eb	*eb, char *ret)
{
	if (eb->srcp)
		free(eb->srcp);
	if (eb->envkey)
		free(eb->envkey);
	if (eb->envval)
		free(eb->envval);
	if (eb->nbr_str)
		free(eb->nbr_str);
	if (eb)
		free(eb);
	return (ret);
}

char	*fetch_env_in_src(t_eb *eb)
{
	char *ret;

	ret = (char *)ft_calloc(sizeof(char), eb->src_l + eb->value_l + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, eb->srcp, eb->now_ix);
	if (eb->envval)
	{
		ft_strncpy(ret + eb->now_ix, eb->envval, eb->value_l);
		ft_strncpy(ret + eb->now_ix + eb->value_l,
					eb->srcp + eb->now_ix + eb->key_l + 1,
					eb->src_l - eb->now_ix - eb->key_l);
	}
	else
	{
		eb->value_l = 0;
		ft_strncpy(ret + eb->now_ix,
					eb->srcp + eb->now_ix + eb->key_l + 1,
					eb->src_l - eb->now_ix - eb->key_l);	
	}
	ret[eb->src_l + eb->value_l] = '\0';
	return (ret);
}

char	*fetch_nbr_in_src(t_eb *eb)
{
	char 	*ret;
	char	*remain_startp;
	int		remain_l;

	ret = (char *)ft_calloc(sizeof(char), eb->src_l + eb->nbr_l + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, eb->srcp, eb->now_ix);
	ft_strncpy(ret + eb->now_ix, eb->nbr_str, eb->nbr_l);
	remain_startp = eb->srcp + eb->now_ix + 2;
	remain_l = eb->src_l - eb->now_ix - 1;
	ft_strncpy(ret + eb->now_ix + eb->nbr_l, remain_startp, remain_l);
	ret[eb->src_l + eb->nbr_l] = '\0';
	return (ret);
}


char	*append_env(char *src, int *now_ix, t_data *data)
{
	char	*ret;
	t_eb	*envbucket;

	printf("check\n");
	envbucket = set_envbucket(src, *now_ix);
	if (!envbucket
		|| search_and_copy_envval(src, envbucket, data))
		return (return_append_env(envbucket, NULL));
	ret = fetch_env_in_src(envbucket);
	if (!ret)
		return (return_append_env(envbucket, NULL));
	*now_ix += envbucket->value_l - 1;
	return (return_append_env(envbucket, ret));
}

int save_target(t_eb *eb, int target)
{
	eb->nbr_str = ft_itoa(target);
	eb->nbr_l = ft_strlen(eb->nbr_str);
	return (0);
}


char	*append_nbr(char *src, int *now_ix, int target)
{
	char	*ret;
	t_eb	*envbucket;

	envbucket = set_envbucket(src, *now_ix);
	if (!envbucket
		|| save_target(envbucket, target))
		return (return_append_env(envbucket, NULL));
	ret = fetch_nbr_in_src(envbucket);
	if (!ret)
		return (return_append_env(envbucket, NULL));
	*now_ix += 2;
	return (return_append_env(envbucket, ret));
}

/*
** envflag ($) checker
*/

int is_envflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && flag != 1);
}

int is_dq(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && str[ix + 1] == '?' && flag != 1);
}

int is_env_print_process(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && str[ix + 1] == '$' && flag != 1);
}

int check_envcnt(const char *str)
{
	int ix;
	int ret;
	int quote_flag;

	ix = -1;
	ret = 0;
	quote_flag = 0;
	while (str[++ix])
	{
		is_inquoted(str, ix, &quote_flag);
		if (is_dq(str, ix, quote_flag) || is_envflag(str, ix, quote_flag))
			ret++;
	}
	if (ret > 0)
		return (TRUE);
	return (FALSE);
}

/*
** main env parsing function
*/
int setup_and_check_env(const char *str, t_data *data)
{
	int ix;
	char *dst;
	int quote_flag;

	ix = -1;
	quote_flag = 0;
	dst = ft_strdup(str);
	if (check_envcnt(dst) == TRUE)
	{
		while (dst[++ix])
		{
			is_inquoted(dst, ix, &quote_flag);
			if (is_dq(dst, ix, quote_flag))
				dst = append_nbr(dst, &ix, g_dq);
			else if (is_env_print_process(dst, ix, quote_flag))
				dst = append_nbr(dst, &ix, getpid());
			else if (is_envflag(dst, ix, quote_flag)
				&& is_start_charset_envkey(dst[ix + 1]))
				dst = append_env(dst, &ix, data);
		}
	}
	data->ip->scenv_ret = dst;
	return (0);
}