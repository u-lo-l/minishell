/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:35:07 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:21:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token_tree	*create_token_tree(void)
{
	return (ft_calloc(1, sizeof(t_token_tree)));
}

void	free_token_tree(t_token_tree *token_tree)
{
	t_command	*target;
	t_command	*next;

	if (token_tree == NULL)
		return ;
	target = token_tree->head_cmd;
	while (target)
	{
		next = target->next_cmd;
		free_command(target);
		target = next;
	}
	free(token_tree);
}

int	add_token_to_tree(t_token_tree *toktree, t_token *tok)
{
	if (!tok)
		return (FALSE);
	if (toktree->head_cmd == NULL)
		if (!add_one_empty_command(toktree))
			return (FALSE);
	return (add_token_to_command(toktree->tail_cmd, tok));
}

int	add_one_empty_command(t_token_tree *token_tree)
{
	t_command	*new_command;

	if (!token_tree)
		return (FALSE);
	new_command = create_empty_command();
	if (new_command == NULL)
		return (FALSE);
	if (token_tree->head_cmd == NULL)
		token_tree->head_cmd = new_command;
	if (token_tree->tail_cmd != NULL)
		token_tree->tail_cmd->next_cmd = new_command;
	token_tree->tail_cmd = new_command;
	token_tree->num_of_commands++;
	return (TRUE);
}
