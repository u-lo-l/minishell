/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:13:26 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/23 20:13:29 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	cd(char **cd_token)
{
	int	ch;

	if (!cd_token || !ft_cmp(cd_token[0], "cd"))
		return ;
	ch = chdir(cd_token[1]);
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

	cd(token);
	pwd();
}
*/
