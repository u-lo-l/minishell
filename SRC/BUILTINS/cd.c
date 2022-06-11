/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:13:26 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 15:36:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>
#include <errno.h>

static int	cd_err(int errcase, char *oldpwd)
{
	free (oldpwd);
	if (errcase == 0)
		return (return_err("cd : HOME is not set", 1));
	else if (errcase == 1)
		return (return_err("cd : too many args", 1));
	if (errno == EACCES)
		return (return_err("cd : permision denied", 1));
	else if (errno == EFAULT)
		return (return_err("cd : path is not accessible", 1));
	else if (errno == EIO)
		return (return_err("cd : I/O error occurs", 1));
	else if (errno == ELOOP)
		return (return_err("cd : too many symbolic links", 1));
	else if (errno == ENAMETOOLONG)
		return (return_err("cd : path is too long", 1));
	else if (errno == ENOENT)
		return (return_err("cd : path is not exist", 1));
	else if (errno == ENOMEM)
		return (return_err("cd : insufficient kernel memory", 1));
	else if (errno == ENOTDIR)
		return (return_err("cd : path is not directory", 1));
	return (return_err("cd : unexpected error", 1));
}

static t_envnode	*find_home(t_env *envlst)
{
	t_envnode	*curr;

	curr = envlst->phead;
	while (curr)
	{
		if (ft_strncmp(curr->key, "HOME", 5) == 0)
			return (curr);
		curr = curr->nextnode;
	}
	return (NULL);
}

static int	set_pwd_env(t_env *envlst, char *oldpwd)
{
	char		*pwd;
	t_envnode	*newnode;

	if (!modify_value(envlst, "OLDPWD", oldpwd))
	{
		newnode = create_envnode("OLDPWD", oldpwd);
		add_node_to_lst(envlst, newnode);
	}
	free (oldpwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (return_err("cd : unexpected error\n", 1));
	if (!modify_value(envlst, "PWD", pwd))
	{
		newnode = create_envnode("PWD", pwd);
		add_node_to_lst(envlst, newnode);
	}
	free (pwd);
	return (0);
}

int	do_cd(t_token_list *toklst, t_env *envlst)
{
	t_envnode	*home_dir;
	t_token		*cd;
	char		*target_dir;
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (return_err("cd : unexpected error\n", 1));
	cd = toklst->head;
	home_dir = find_home(envlst);
	if (cd->next == NULL && home_dir != NULL)
		target_dir = home_dir->value;
	else if (cd->next == NULL && home_dir == NULL)
		return (cd_err(0, old_pwd));
	else if (cd->next->next != NULL)
		return (cd_err(1, old_pwd));
	else
		target_dir = cd->next->text;
	if (target_dir == NULL)
		return (cd_err(0, old_pwd));
	if (chdir(target_dir))
		return (cd_err(2, old_pwd));
	return (set_pwd_env(envlst, old_pwd));
}
