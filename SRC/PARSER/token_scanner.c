/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_scanner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:44 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/27 14:04:09 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static int 	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}

static int	is_redir_op(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

t_token_tree *scan_token(t_input *input, t_env *env_list)
{
	t_token_tree		*toktree;
	char				*word;
	enum e_token_type	type;

	if (input == NULL || env_list == NULL)
		return (NULL);
	toktree = create_token_tree();
	add_one_empty_command(toktree);
	skip_space(input);
	word = NULL;
	type = e_word;
	while (TRUE)
	{
		if (is_quote(input->cmd[input->curr_i]) == TRUE)
			quote_case(input, &word, env_list);
		else if (ft_strchr(" \t", input->cmd[input->curr_i]))
		{
			if (split_token(toktree, input, &word, type) == 0)
				break ;
			type = e_word;
		}
		else if (input->cmd[input->curr_i] == '$')
			dollar_case(input, &word, env_list);
		else if (input->cmd[input->curr_i] == '|')
		{
			input->curr_i++;
			skip_space(input);
			if (ft_strchr("|", input->cmd[input->curr_i]))
			{
				free_token_tree(toktree);
				return (NULL);
			}
			add_one_empty_command(toktree);
		}
		else if (is_redir_op(input->cmd[input->curr_i]) == TRUE)
		{
			if (input->cmd[input->curr_i++] == '>')
			{
				type = e_outrdr;
				input->start_i = input->curr_i;
				if (input->cmd[input->curr_i++] == '>')
				{
					input->start_i = input->curr_i;
					type = e_appendrdr;
				}
			}
			else
			{
				type = e_inrdr;
				input->start_i = input->curr_i;
				if (input->cmd[input->curr_i++] == '<')
				{
					input->start_i = input->curr_i;
					type = e_heredoc;
				}
			}
			skip_space(input);
		}
		else
			input->curr_i++;
	}
	return (toktree);
}
/*
int main(int argc, char **argv, char **envp)
{
	t_input 		*input;
	t_env			*envs;
	t_token_tree	*cmd_token_tree;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (0);
	envs = env_list(envp);
	while (1)
	{
		// 명령어 한 줄 읽어오기
		input = read_command("mini >>  ");
		if (input == NULL)
			break ;
		// printf("input : <%s>\n", input->cmd);
		cmd_token_tree = scan_token(input, envs);
		free(input->cmd);
		free(input);
		print_token_tree(cmd_token_tree);
		if (cmd_token_tree == NULL)
			printf("BAD SYNTAX\n");
		free_token_tree(cmd_token_tree);
	}
	free_env_list(envs);
	return (0);
}
*/