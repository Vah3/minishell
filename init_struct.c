/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:14:27 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/21 14:40:29 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	struct_zeroed(t_pars **pars, t_env **env)
{
	t_pars	*var;

	var = *pars;
	var->apendfiles = NULL;
	var->cmd = NULL;
	var->env_var = env;
	var->errfile = NULL;
	var->fileordoc = -1;
	var->heredocs = 0;
	var->infilefd = 0;
	var->infiles = 0;
	var->isheredoc = 0;
	var->outfilefd = 0;
	var->outfiles = 0;
	var->pipecount = 0;
	var->app_or_trunc = -1;
	var->errnum = 0;
}

t_pars	**init_struct(int count, t_env **env)
{
	t_pars	**pars;
	int		i;

	i = 0;
	pars = (t_pars **)malloc(sizeof(t_pars *) * (count + 1));
	if (!pars)
		return (0);
	pars[count] = NULL;
	while (i < count)
	{
		pars[i] = (t_pars *)malloc(sizeof(t_pars));
		if (!pars[i])
		{
			while (i >= 0)
			{
				free (pars[i]);
				i--;
			}
			free(pars);
			return (0);
		}
		struct_zeroed(&pars[i], env);
		i++;
	}
	return (pars);
}
