/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:51 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 17:26:44 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	do_unset(t_token_list *unset_token, t_env *envlst)
{
	t_token	*curr_tok;

	curr_tok = unset_token->head;
	envlst->error = 0;
	if (ft_strncmp(curr_tok->text, "unset", 6) != 0)
		return (return_err("unset : unexpected error", 1));
	curr_tok = curr_tok->next;
	while (curr_tok)
	{
		if (is_env_name(curr_tok->text) == FALSE)
		{
			envlst->error = 1;
			ft_putstr_fd("minishell : unset : invalid syntax : '", 2);
			ft_putstr_fd(curr_tok->text, 2);
			ft_putstr_fd("'\n", 2);
		}
		else
			del_node_from_lst(envlst, curr_tok->text);
		curr_tok = curr_tok->next;
	}
	return (envlst->error);
}
