/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_special_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 07:29:50 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 21:16:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

int	case_space(t_token_tree *toktree, t_input *input, \
				char **pword, int *type)
{
	if (set_word(input, pword) == FALSE)
		return (FALSE);
	pass_space_tab(input);
	if (delimit_and_add_token_to_tree(toktree, pword, type) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	case_pipe(t_token_tree *toktree, t_input *input, \
				char **pword, int *type)
{
	char	*new_cmdline;

	if (set_word(input, pword) == FALSE)
		return (FALSE);
	input->start_i = ++input->curr_i;
	if (delimit_and_add_token_to_tree(toktree, pword, type) == FALSE)
		return (FALSE);
	pass_space_tab(input);
	if (add_one_empty_command(toktree) == FALSE)
		return (FALSE);
	new_cmdline = ft_strdup(&input->cmd[input->start_i]);
	if (!new_cmdline)
		return (FALSE);
	free(input->cmd);
	input->cmd = new_cmdline;
	input->start_i = 0;
	input->curr_i = 0;
	if (input->cmd[input->start_i] == '|')
		return (FALSE);
	return (TRUE);
}

int	case_dollar(t_input *input, t_env *envlst, char **pword, int type)
{
	char	*expanded_word;

	if (set_word(input, pword) == FALSE)
		return (FALSE);
	if (ft_strchr(" \'\"\t<>$|\0", input->cmd[++input->curr_i]) != NULL)
	{
		if ((type & QUOTE) == QUOTE)
			return (TRUE);
		if (is_quote(input->cmd[input->curr_i]) == TRUE)
			input->start_i = input->curr_i;
		return (TRUE);
	}
	input->start_i = input->curr_i;
	expanded_word = expand_variable(input, envlst);
	if (expanded_word == NULL)
		return (FALSE);
	if (expanded_word[0] == 0)
	{
		if ((*pword == NULL) && (type != WORD))
			*pword = ft_strdup("");
		free(expanded_word);
		return (TRUE);
	}
	else
		return (case_dollar_util(pword, expanded_word));
}

int	case_quote(t_input *input, t_env *envlst, char **pword, int type)
{
	char	quote;

	quote = input->cmd[input->curr_i];
	type |= QUOTE;
	if (set_word(input, pword) == FALSE)
		return (FALSE);
	input->start_i = ++input->curr_i;
	if (ft_strchr(input->cmd + input->curr_i, quote) == NULL)
		return (FALSE);
	while (input->cmd[input->curr_i] != quote)
	{
		if (input->cmd[input->curr_i++] == '$' && \
			(quote == '"') && ((type & HEREDOC) != HEREDOC))
		{
			input->curr_i--;
			if (case_dollar(input, envlst, pword, type) == FALSE)
				return (FALSE);
		}
	}
	if (input->curr_i == input->start_i && *pword == NULL)
		*pword = ft_strdup("");
	else if (set_word(input, pword) == FALSE)
		return (FALSE);
	input->start_i = ++input->curr_i;
	return (TRUE);
}

int	case_redirection(t_token_tree *toktree, t_input *input, \
					char **pword, int *type)
{
	char	operator;

	operator = input->cmd[input->curr_i];
	if (case_space(toktree, input, pword, type) == FALSE)
		return (FALSE);
	*type = INRDR;
	if (operator == '>')
		*type = OUTRDR;
	if (input->cmd[++input->curr_i] == operator)
	{
		*type = HEREDOC;
		if (operator == '>')
			*type = APNDRDR;
		input->curr_i++;
	}
	pass_space_tab(input);
	if (ft_strchr("|<>\0", input->cmd[input->curr_i]) != NULL)
		return (FALSE);
	return (TRUE);
}
