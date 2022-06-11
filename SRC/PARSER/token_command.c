/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:07:15 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:22:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_command	*create_empty_command(void)
{
	t_command	*new_command;

	new_command = ft_calloc(1, sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	new_command->simple_command = create_empty_toklst();
	new_command->input_redir = create_empty_toklst();
	new_command->output_redir = create_empty_toklst();
	new_command->here_doc = create_empty_toklst();
	new_command->redirection = create_empty_toklst();
	if (!new_command->simple_command || !new_command->here_doc || \
		!new_command->input_redir || !new_command->output_redir)
	{
		free_command(new_command);
		return (NULL);
	}
	return (new_command);
}

void	free_command(t_command *command)
{
	if (command == NULL)
		return ;
	free_toklst(command->simple_command);
	free_toklst(command->input_redir);
	free_toklst(command->output_redir);
	free_toklst(command->here_doc);
	free_toklst(command->redirection);
	free(command);
}

static t_token	*temp_duptok(t_token *tok)
{
	t_token	*temp;

	temp = create_token(tok->text, tok->type);
	if (!temp)
		exit(100);
	return (temp);
}

int	add_token_to_command(t_command *command, t_token *tok)
{
	int		res;
	t_token	*temp;

	if (!command || !tok)
		return (FALSE);
	if (tok->type == e_word)
		res = add_token_to_toklst(command->simple_command, tok);
	else if (tok->type == e_inrdr)
		res = add_token_to_toklst(command->input_redir, tok);
	else if (tok->type == e_outrdr || tok->type == e_appendrdr)
		res = add_token_to_toklst(command->output_redir, tok);
	else if (tok->type == e_heredoc)
		res = add_token_to_toklst(command->here_doc, tok);
	else
	{
		res = 0;
		ft_putstr_fd("bad token", 2);
	}
	if (tok->type == e_inrdr || \
		tok->type == e_outrdr || tok->type == e_appendrdr)
	{
		temp = temp_duptok(tok);
		res = add_token_to_toklst(command->redirection, temp);
	}
	return (res);
}
