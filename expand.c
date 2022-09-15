/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:06:18 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/15 20:09:52 by vagevorg         ###   ########.fr       */
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
		while(line_[j] && line_[j] != 39)
		{
			j++;
			(*len)++;
		}
		j++;
		(*len)++;
	}
	*i = j;
}

char	*find_var(t_env *env, char	*env_var)
{
	while(env)
	{
		if(strncmp(env->key, env_var, ft_strlen(env->key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (0);
}
void	if_dollar_sign(char	**promt, int *i, int *len, t_env *env_v)
{
	char	*delim = NULL;
//	char	*line;
	char	*prom;
	int		j;

	j = 0;
	if ((*promt)[*i] == '$')
	{
		(*i)++;
	/*	if ((*promt)[*i] == 39 && (*promt)[(*i)++])
		{
			while((*promt)[*i] && (*promt)[*i] != 39)
			{
				(*i)++;
				(*len)++;
			}
		}
		else if ((*promt)[*i] == 34 && (*promt)[(*i)++])
		{
			j = *i;
			while((*promt)[*i] && (*promt)[*i] != 34)
				(*i)++;
			delim = ft_substr(*promt, j, (*i) - j); //leaki
			if ( (j == 2 || (*promt)[j - 3] == 32) && (((*promt)[(*i) + 1] == '\0') || ((*promt)[(*i) + 1] == 32)))
				delim = _getenv(env_v, delim);
			*len += ft_strlen(delim);
			(*promt)[j - 2] = 0;
			prom = ft_strdup(*promt);
			prom = ft_strjoin(prom, delim);
			prom = ft_strjoin(prom, (*promt) + (*i) + 1);

			*promt = prom;
			*i = *len - 1;
			//len += ft_strlen(delim); //////stex leak ka
//			free(delim);
		}
		else*/
		//{
			j = *i;
			while((*promt)[*i] && /*!ft_isdigit((*promt)[j]) && */ft_isalnum((*promt)[*i]))
				(*i)++;
			delim = ft_substr(*promt, j, (*i) - j); //leak ka
		//	*len += ft_strlen(delim);
			delim = _getenv(env_v, delim);
			*len += ft_strlen(delim);
			(*promt)[j - 1] = 0;
			prom = ft_strdup(*promt);
			prom = ft_strjoin(prom, delim);
			prom = ft_strjoin(prom, (*promt) + (*i));
			*promt = prom;//*promt leak

		//	*len += ft_strlen(delim); //////stex el, vortev copy a 
		//	free(delim);
			(*i)--;
		(*len)--;
	}
}
	

void	do_expand(char	**promt, t_env *env_)
{
	int		len;
	int		i;
//	char	*line;

	i = 0;
	len = 0;
	while (*promt && (*promt)[i])
	{
		skip_if_single_quote(promt, &i, &len);
		if_dollar_sign(promt, &i, &len, env_);
		len++;
		i++;
	}
}

