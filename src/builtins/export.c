/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:01:03 by cpothin           #+#    #+#             */
/*   Updated: 2023/09/25 14:40:32 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

/*
	Check if the argument given contains a `=` sign.
	@param `*arg`: argument given to the command.
	@return `true` or `false` - depending if the condition is met.
*/
bool	check_arg_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i++] == '=')
			return (true);
	}
	return (false);
}

/*
	Check and edit a variable to the environment list.
	@param `*data`: environment of the minishell.
	@param `*arg`: argument given as a variable.
	@param `*short_var`: name of the variable to edit.
*/
void	edit_env_var(t_data *data, char *arg, char *short_var)
{
	t_env	*lst;

	if (check_arg_value(arg) == 0)
		return ;
	lst = data->lst_env;
	while (lst)
	{
		if (ft_strcmp(lst->key, short_var) == 0)
		{
			lst->has_value = true;
			lst->val = new_env_val(lst, arg);
			return ;
		}
		lst = lst->next;
	}
}

/*
	Add a new variable to the environment.
	@param `*data`: environment of minishell.
	@param `*arg`: argument given as a variable.
*/
void	new_env_var(t_data *data, char *arg)
{
	t_env	*lst;

	lst = data->lst_env;
	while (lst)
	{
		if (!lst->next)
		{
			lst->next = split_env(arg);
			return ;
		}
		lst = lst->next;
	}
}

/*
	Check if the environment variable exist, and either
	add or edit the variable given to the environment list.
	@param `*data`: environment of minishell.
	@param `*arg`: variable given.
*/
void	export_var(t_data *data, char *arg)
{
	bool	exists;
	t_env	*lst;
	char	*short_var;

	exists = false;
	lst = data->lst_env;
	short_var = get_short_var(arg);
	while (lst)
	{
		if (ft_strcmp(lst->key, short_var) == 0)
		{
			exists = true;
			break ;
		}
		lst = lst->next;
	}
	if (exists)
		edit_env_var(data, arg, short_var);
	else
		new_env_var(data, arg);
	gc_free(short_var);
}

/*
	Check if the export command has an argument or not.
	If there is an argument, either add it or edit the environment list.
	If not, prints out the environment list formatted and in alphabetical
	order.
	@param `*data`: environment of minishell.
	@returns `g_status` - int of the exit code of the command.
*/
int	do_export(t_data *data)
{
	int	i;

	i = 1;
	if (data->args->argc == 1)
		return (set_g_status(single_export(data)));
	while (data->args->argv[i])
	{
		if (ft_isalpha(data->args->argv[i][0]))
			export_var(data, data->args->argv[i]);
		else
		{
			ft_printf("minishell: export: %s: \
not a valid identifier\n", data->args->argv[i]);
			return (set_g_status(ERROR));
		}
		i++;
	}
	re_store_env(data);
	return (set_g_status(SUCCESS));
}
