/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:35:07 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/25 21:59:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

t_token_arr	*create_token_arr(void)
{
	return (ft_calloc(1, sizeof(t_token_arr)));
}

void	 free_token_arr(t_token_arr *token_arr)
{
	if (token_arr == NULL)
		return ;
	free_commands(token_arr->commads);
	free(token_arr);
}

int	add_command(t_token_arr *token_arr, t_command *new_command)
{
	if (!token_arr)
		return (FALSE);
		
}