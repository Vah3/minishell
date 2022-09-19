/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:06:18 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/19 17:45:34 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_if_single_quote(char **line, int *i, int *len)
{
	int		j;
	char	*line_;

	j = *i;
	line_ = *line;
	if (line_ && line_[j] && line_[j] == 39)
	{
		j++;
		(*len)++;
		while (line_[j] && line_[j] != 39)
		{
			j++;
			(*len)++;
		}
		j++;
		(*len)++;
	}
	*i = j;
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

void	if_dollar_sign(char	**promt, int *i, int *len, t_env *env_v)
{
	char	*delim;
	char	*prom;
	char	*for_free;
	int		j;

	delim = NULL;
	j = 0;
	if ((*promt)[*i] == '$')
	{
		(*i)++;
		j = *i;
		while ((*promt)[*i] && (ft_isalnum((*promt)[*i]) || (*promt)[*i] == '?'))
			(*i)++;
		delim = ft_substr(*promt, j, (*i) - j);
		for_free = delim;
		delim = _getenv(env_v, delim);
		free(for_free);
		*len += ft_strlen(delim);
		(*promt)[j - 1] = 0;
		prom = ft_strdup(*promt);
		prom = ft_strjoin(prom, delim);
		prom = ft_strjoin(prom, (*promt) + (*i));
		free (*promt);
		free (delim);
		*promt = prom;
		(*i)--;
		(*len)--;
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
			skip_if_single_quote(promt, &i, &len);
		if_dollar_sign(promt, &i, &len, env_);
		len++;
		i++;
	}
}
