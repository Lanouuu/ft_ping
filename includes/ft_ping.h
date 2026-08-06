#ifndef FT_PING
# define FT_PING

# include <stdio.h>
# include <string.h>

enum errors {
    MISS_HOST_OP,
    TOO_MUCH_OP,
    BAD_OP,
    BAD_OPT,
    HELP_ERR,
};

typedef struct s_stats {

} t_stats;

typedef struct s_ping {
    // options
    int     verbose;
    int     help;
    char    *str_count;
    long    count;

    char    *hostname;
} t_ping;

int     dispatch_err(int err, char *s);
void    print_help(void);

void    init_data(t_ping *data);
int     parser(char **av, t_ping *data);

#endif