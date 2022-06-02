#include "../INC/minishell.h"

int	return_err(char *errstr, int ret_val)
{
	ft_putstr_fd(errstr, 2);
	ft_putstr_fd("\n", 2);
	return (ret_val);
}
