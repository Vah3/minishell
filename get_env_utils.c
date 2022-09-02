#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = NULL;
	}
}

t_env	*last_env_element(t_env *start)
{
	if (start == NULL)
		return (NULL);
	if (start->next == NULL)
		return (start);
	else
		return (last_env_element(start->next));
}



int	size_of_list(t_env *list)
{
	if (list == NULL)
		return (0);
	else
		return (1 + size_of_list(list->next));
}

void	free_after_split(char **store)
{
	int	i;

	i = 0;
	while (store[i])
	{
		free(store[i]);
		store[i] = NULL;
		i++;
	}
	free(store);
}


int	size_of_env(char **env)
{
	int	length;

	length = 0;
	while (env[length] != NULL)
		length++;
	return (length);
}