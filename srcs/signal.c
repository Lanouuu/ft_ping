#include "ft_ping.h"

volatile sig_atomic_t   stop = 0;

static void	ctrl_c_handler(int signal) {
	(void)signal;
	stop = 1;
	fprintf(stdout, "\n");
	return ;
}

int	signals_handler(void) {
	struct sigaction	ctrl_c;

	errno = 0;
	memset(&ctrl_c, 0, sizeof(ctrl_c));
	if (sigemptyset(&ctrl_c.sa_mask) == -1)
		return (dispatch_err(SIG_SET, NULL, errno));
	ctrl_c.sa_flags = 0;
	ctrl_c.sa_handler = &ctrl_c_handler;
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		return (dispatch_err(SIG_ACT, NULL, errno));
	return (0);
}