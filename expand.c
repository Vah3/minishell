/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:06:18 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/11 17:01:05 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	skip_if_single_quote(char *line, int *i, int *len)
{
	int		j;

	j = *i;
	if (line && line[j] && line[j] == 39)
	{
		if (*i > 0 && line[(*i) - 1] == '\\')
		{
			*i += 1;
			*len += 1;
			return ;
		}
		j++;
		while (line[j] && line[j] != 39)
		{
			if (line[j] == '\\')
				j++;
			if (line[j])
				j++;
		}
	}
	*i = j;
	*len = j;
}

static void	free_params(char	*delim, char	*promt)
{
	free (promt);
	free(delim);
}

char	*join(char *promt, int i, char *delim, char *env_line)
{
	char	*prom;

	prom = ft_strdup(promt);
	prom = ft_strjoin(prom, env_line);
	prom = ft_strjoin(prom, promt + i);
	free_params(delim, promt);
	return (prom);
}

static void	if_dollar_sign(char	**promt, int *i, int *len, t_env *env_v)
{
	char	*delim;
	char	*env_line;
	int		j;

	delim = NULL;
	j = 0;
	if ((*promt)[*i] == '$' && (*promt)[++(*i)])
	{
		j = *i;
		while ((*promt)[*i] && (ft_isalnum((*promt)[*i])
			|| (*promt)[*i] == '?' || (*promt)[*i] == '_'))
			(*i)++;
		delim = ft_substr(*promt, j, (*i) - j);
		delim = change_delim_key(delim);
		env_line = _getenv(env_v, delim);
		*len += ft_strlen(env_line);
		(*promt)[j - 1] = 0;
		*promt = join(*promt, *i, delim, env_line);
		(*i) = (*len) - 1;
		if ((*i) == -1)
			*i = 0;
		(*len)--;
	}
}

void	do_expand(char **promt, t_env *env, int doc)
{
	int		len;
	int		i;
	t_env	*env_;
	int		in_double_quote;

	i = 0;
	len = 0;
	in_double_quote = 1;
	env_ = env;
	while (*promt && (*promt)[i])
	{
		if (doc == 0 && in_double_quote)
			skip_if_single_quote(*promt, &i, &len);
		if ((*promt)[i] == '"' && in_double_quote == 1)
			in_double_quote = 0;
		else if ((*promt)[i] == '"' && in_double_quote == 0)
			in_double_quote = 1;
		if_dollar_sign(promt, &i, &len, env_);
		if ((*promt)[i])
		{
			i++;
			len++;
		}
	}
}
