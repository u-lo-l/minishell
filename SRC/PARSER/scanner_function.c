/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 06:56:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 21:14:55 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	scanning_loop(t_token_tree *toktree, t_input \
							*input, t_env *envlst, char **pword)
{
	int	res;
	int	type;

	res = TRUE;
	type = WORD;
	while (res == TRUE)
	{
		if (is_space(input->cmd[input->curr_i]) == TRUE)
			res = case_space(toktree, input, pword, &type);
		else if (input->cmd[input->curr_i] == '|')
			res = case_pipe(toktree, input, pword, &type);
		else if (input->cmd[input->curr_i] == '$' && type != HEREDOC)
			res = case_dollar(input, envlst, pword, type);
		else if (is_quote(input->cmd[input->curr_i]) == TRUE)
			res = case_quote(input, envlst, pword, type);
		else if (is_redir_op(input->cmd[input->curr_i]) == TRUE)
			res = case_redirection(toktree, input, pword, &type);
		else if (input->cmd[input->curr_i] == '\0')
			return (case_space(toktree, input, pword, &type));
		else
			input->curr_i++;
	}
	return (res);
}

t_token_tree	*tokenize_and_parsing(t_input *input, t_env *envlst)
{
	t_token_tree	*toktree;
	char			*word;

	if (input->cmd[0] == '|' || input->cmd[ft_strlen(input->cmd) - 1] == '|')
		return (NULL);
	toktree = create_token_tree();
	if (toktree == NULL)
		return (NULL);
	word = NULL;
	if (scanning_loop(toktree, input, envlst, &word) == FALSE)
	{
		free_token_tree(toktree);
		toktree = NULL;
	}
	free(word);
	return (toktree);
}
