/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:51 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 16:11:50 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	do_unset(t_token_list *unset_token, t_env *envlst)
{
	t_token	*curr_tok;

	curr_tok = unset_token->head;
	if (ft_strncmp(curr_tok->text, "unset", 6) != 0)
	{
		envlst->error = 1;
		return (return_err("unset : unexpected error", 1));
	}
	curr_tok = curr_tok->next;
	while (curr_tok)
	{
		del_node_from_lst(envlst, curr_tok->text);
		curr_tok = curr_tok->next;
	}
	return (0);
}
