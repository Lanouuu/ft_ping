#ifndef FT_PING
# define FT_PING

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>

# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

enum errors {
    MISS_HOST_OP,
    TOO_MUCH_OP,
    BAD_OP,
    BAD_OPT,
    HELP_ERR,
    INV_COUNT,
    GAI_ERR,
    SOCK_ERR,
};

// typedef struct s_stats {

// } t_stats;

typedef struct s_ping {
    // options
    int                 verbose;
    int                 help;
    char                *str_count;
    int                 count;

    char                *hostname;
    struct sockaddr_in  addr;

    int                 sockfd;
} t_ping;

int     dispatch_err(int err, char *s, int ret);
void    print_help(void);

void    init_data(t_ping *data);
int     parser(char **av, t_ping *data);
int     resolve_host(t_ping *data);
int     init_socket(t_ping *data);

#endif