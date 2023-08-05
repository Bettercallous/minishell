/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/05 13:02:18 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	must_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	handle_expand(t_list **list, t_vars *vars, t_env *env)
{
	if (must_expand((*list)->token->value))
	{
		(*list)->token->value = expand_((*list)->token->value, env);
		(*list)->token->expanded = 1;
		if (is_quotes(vars->prev))
			(*list)->token->in_quotes = 1;
	}
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	mark_quotes(t_list **list, t_vars *vars)
{
	vars->in_quotes = !vars->in_quotes;
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	expansion(t_list *list, t_env *env)
{
	t_vars	*vars;

	vars = init_vars();
	while (list)
	{
		if (list->token->type == S_QUOTES)
			mark_quotes(&list, vars);
		else if (list->token->type == WHITESPACE)
			list = list->next;
		else if (list->token->type == WORD && vars->prev == S_QUOTES
			&& vars->in_quotes)
		{
			vars->prev = list->token->type;
			list = list->next;
		}
		else if (list->token->type == WORD && vars->prev != HEREDOC)
			handle_expand(&list, vars, env);
		else
		{
			vars->prev = list->token->type;
			list = list->next;
		}
	}
	free(vars);
}
