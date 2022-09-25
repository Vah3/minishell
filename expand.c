/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:06:18 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/20 14:27:15 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_if_single_quote(char *line, int *i, int *len)
{
	int		j;

	j = *i;
	if (line && line[j] && line[j] == 39)
	{
		if (*i > 0 && line[(*i) - 1] == '\\')
		{
			*i += 1;
			return ;
		}
		j++;
		(*len)++;
		while (line[j] && line[j] != 39)
		{
			if (line[j] == '\\')
				j++;
			if (line[j])
				j++;
			(*len)++;
		}
		j++;
		(*len)++;
	}
	*i = j;
}

static void	free_params(char	*delim, char	*promt, char	*env_line)
{
	free (promt);
	free(delim);
	free (env_line);
}

static void	if_dollar_sign(char	**promt, int *i, int *len, t_env *env_v)
{
	char	*delim;
	char	*prom;
	char	*env_line;
	int		j;

	delim = NULL;
	j = 0;
	if ((*promt)[*i] == '$' && (*promt)[++(*i)])
	{
		j = *i;
		while ((*promt)[*i]
				&& (ft_isalnum((*promt)[*i]) || (*promt)[*i] == '?' || (*promt)[*i] == '_'))
			(*i)++;
		delim = ft_substr(*promt, j, (*i) - j);
		env_line = _getenv(env_v, delim);
		*len += ft_strlen(env_line);
		(*promt)[j - 1] = 0;
		prom = ft_strdup(*promt);
		prom = ft_strjoin(prom, env_line);
		prom = ft_strjoin(prom, (*promt) + (*i));
		free_params(delim, *promt, env_line);
		*promt = prom;
		(*i)--;
		(*len)--;
	}
}

void	update_status(t_env *env, int status)
{
	t_env	*local_env;
	char	*stat;

	local_env = env;
	stat = ft_itoa(status);
	while (local_env)
	{
		if (strncmp(local_env->key, "?", 1) == 0)
		{
			free(local_env->value);
			local_env->value = stat;
		}
		local_env = local_env->next;
	}
}

void	do_expand(char **promt, t_env *env_, int doc)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (*promt && (*promt)[i])
	{
		if (doc == 0)
			skip_if_single_quote(*promt, &i, &len);
		if_dollar_sign(promt, &i, &len, env_);
		len++;
		i++;
	}
}
