#include "minishell.h"

void	struct_zeroed(t_pars **pars)
{
	t_pars *var;

	var = *pars;
	var->apendfiles = NULL;
	var->cmd = NULL;
	var->env_var = NULL;
	var->errfile = NULL;
	var->fileordoc = 0;
	var->heredocs = 0;
	var->infilefd = 0;
	var->infiles = 0;
	var->isheredoc = 0;
	var->outfilefd = 0;
	var->outfiles = 0;
	var->pipecount = 0;
}

t_pars	**init_struct(int count)
{
	t_pars	**pars;
	int	i;

	i = 0;
	pars =(t_pars **)malloc(sizeof(t_pars *) * (count + 1));
	if (!pars)
		return (0);
	pars[count] = NULL;
	while (i < count)
	{
		pars[i] = (t_pars *)malloc(sizeof(t_pars));
		if (!pars[i])
		{
			while(i >= 0)
			{
				free (pars[i]);
				i--;
			}
			free(pars);
			return (0);
		}
		struct_zeroed(&pars[i]);
		i++;
	}
	return (pars);
}