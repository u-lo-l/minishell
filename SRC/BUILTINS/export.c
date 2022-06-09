/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:52:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/09 17:43:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static int	export_error(char *key_and_value)
{
	ft_putstr_fd("minishell : export : invalid syntax : \"", 2);
	ft_putstr_fd(key_and_value, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static void	free_key_and_value(char *key_and_value[2])
{
	free(key_and_value[0]);
	free(key_and_value[1]);
}

int	do_export(t_token_list *toklst, t_env *envlst)
{
	t_envnode	*newnode;
	t_token		*curr_tok;
	char		*key_and_value[2];
	int			result;

	result = 0;
	if (toklst->num_of_tokens == 1)
		return (show_shell_var_asscending(envlst));
	curr_tok = toklst->head->next;
	while (curr_tok)
	{
		ft_bzero(key_and_value, sizeof(char *) * 2);
		seperate_keyvalue(curr_tok->text, &key_and_value[0], &key_and_value[1]);
		if (is_env_name(key_and_value[0]) == FALSE)
			result = export_error(curr_tok->text);
		else if (!modify_value(envlst, key_and_value[0], key_and_value[1]))
		{
			newnode = create_envnode(key_and_value[0], key_and_value[1]);
			add_node_to_lst(envlst, newnode);
		}
		free_key_and_value(key_and_value);
		curr_tok = curr_tok->next;
	}
	return (result);
}
