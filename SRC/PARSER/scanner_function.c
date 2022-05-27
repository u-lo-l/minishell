/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 06:56:42 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/28 07:28:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token_tree	*tokenize_and_parsing(t_input *input, t_env *envlst)
{
	t_token_tree*		toktree;
	char				*word;
	enum e_token_type	type;
	int 				res;

	if (input->cmd[0] == '|' || input->cmd[ft_strlen(input->cmd) - 1] == '|')
		return (NULL);
	toktree = create_token_tree();
	word = NULL;
	type = e_word;
	res = TRUE;
	while (res == TRUE)
	{
		if (is_space(input->cmd[input->curr_i]) == TRUE)
			res = case_space(toktree, input, &word, &type);
		else if (input->cmd[input->curr_i] == '|')
			res = case_pipe(toktree, input, &word, &type);
		else if (input->cmd[input->curr_i] == '$')
			res = case_dollar(input, envlst, &word);
		else if (is_quote(input->cmd[input->curr_i]) == TRUE)
			res = case_quote(input, envlst, &word);
		else if (is_redir_op(input->cmd[input->curr_i]) == TRUE)
			res = case_redirection(toktree, input, &word, &type);
		else if (input->cmd[input->curr_i] == '\0')
		{
			res =case_space(toktree, input, &word, &type);
			break ;
		}
		else
			input->curr_i++;
	}
	if (res == FALSE)
	{
		free_token_tree(toktree);
		toktree = NULL;
	}
	free(word);
	return (toktree);
}