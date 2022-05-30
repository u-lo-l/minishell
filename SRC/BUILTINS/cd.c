/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:13:26 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/30 18:31:24 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	do_cd(t_token_list *cd_token)
{
	int	ch;

	ch = chdir(cd_token->head->next->text);
	if (ch != 0)
		printf("no such file or directory");
}
/*
int main()
{
	char **token;

	token = malloc(sizeof(char *) * 2);
	token[0] = malloc(sizeof(char) * 3);
	token[1] = malloc(sizeof(char) * 3);

	token[0] = "cd";
	token[1] = "../../";

	do_cd(token);
	pwd();
}
*/
