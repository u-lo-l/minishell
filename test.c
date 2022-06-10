#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void	sig(int signo)
{
	dprintf(2, "Ctrl+C!\n");
	exit(signo);
}

int main()
{
	while (1);
}
