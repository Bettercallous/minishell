/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:40:04 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/05/26 18:40:04 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exitcode;

int	count_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	remove_nulls(t_list **head)
{
	t_list *current;
	t_list *prev;
	int		prev_type;

	prev = NULL;
	current = *head;
	prev_type = -1;
	while (current != NULL)
	{
		if (current->token->type == WORD && !is_quotes(prev_type) && current->token->value[0] == '\0' && !is_redir(prev_type))
		{
			prev_type = current->token->type;
			if (prev == NULL)
			{
				*head = current->next;
				ft_lstdelone(current, &free);
				current = *head;
			}
			else
			{
				prev->next = current->next;
				ft_lstdelone(current, &free);
				current = prev->next;
			}
		}
		else
		{
			prev_type = current->token->type;
			prev = current;
			current = current->next;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int			err;
	char		*line;
	t_lexer		*lexer;
	t_hdc		*hdc;
	t_list		*tmp_list;
	t_list		*lex_list;
	t_parser	*p_list;
	t_env		*env;
	// t_env		*courant;
	// char		**envvv;
	// int i = 0;
	// int id;
	// int status;

	(void)ac;
	(void)av;
	hdc = NULL;
	tmp_list = NULL;
	lex_list = NULL;
	line = readline("minishell-1.0$ ");
	// signals_handler(line);
	env = get_env(envp);
	while (line)
	{
		add_history(line);
		lexer = init_lexer(line);
		ft_lexer(lexer, &tmp_list, env);
		expansion(tmp_list, env);
		err = check_errors(line, tmp_list);
		if (err != 1 && err != 2)
			exitcode = 258;
		if (err != -1)
		{
			join_words(&lex_list, tmp_list);
			remove_type(&lex_list, WHITESPACE);
			hdc = here_doc(lexer, lex_list, env);
			remove_nulls(&lex_list);
			remove_type(&lex_list, S_QUOTES);
			remove_type(&lex_list, D_QUOTES);
			if (err == 1)
			{
				p_list = ft_parser(lex_list, hdc);
				init_fds(p_list);
				set_pipes(p_list);
				executor(p_list, env, envp);
				free_plist(&p_list);
			}
		}
		free_list(&lex_list);
		free_list(&tmp_list);
		free_lexer(lexer);
		if (hdc)
			free_hdc(hdc);
		line = readline("minishell-1.0$ ");
	}
	return (0);
}
