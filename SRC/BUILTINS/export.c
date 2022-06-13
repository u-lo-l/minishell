/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:52:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 22:48:15 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static int	export_error(char *key_and_value)
{
	ft_putstr_fd("minishell : export : invalid syntax : '", 2);
	ft_putstr_fd(key_and_value, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static void	free_key_and_value(char *key_and_value[2])
{
	free(key_and_value[0]);
	free(key_and_value[1]);
}

static int	export_args(t_env *envlst, t_token *curr_tok, char *key_value[2])
{
	t_envnode	*newnode;

	ft_bzero(key_value, sizeof(char *) * 2);
	if (!seperate_keyvalue(curr_tok->text, &key_value[0], &key_value[1]))
	{
		free(key_value[0]);
		free(key_value[1]);
		return (FALSE);
	}
	if (is_env_name(key_value[0]) == FALSE)
	{
		free(key_value[0]);
		free(key_value[1]);
		return (FALSE);
	}
	else if (!modify_value(envlst, key_value[0], key_value[1]))
	{
		newnode = create_envnode(key_value[0], key_value[1]);
		add_node_to_lst(envlst, newnode);
	}
	free_key_and_value(key_value);
	return (TRUE);
}

int	do_export(t_token_list *toklst, t_env *envlst)
{
	t_token		*curr_tok;
	char		*key_and_value[2];
	int			result;

	result = 0;
	if (toklst->num_of_tokens == 1)
		return (show_shell_var_asscending(envlst));
	curr_tok = toklst->head->next;
	while (curr_tok)
	{
		if (!export_args(envlst, curr_tok, key_and_value))
			result = export_error(curr_tok->text);
		curr_tok = curr_tok->next;
	}
	return (result);
}
