#include "ft_ping.h"

static int check_opt(int *i, char **av, char *opt, t_ping *data) {
    if (strcmp(opt, "-?") == 0)
        data->help = 1;
    else if (strcmp(opt, "-v") == 0)
        data->verbose = 1;
    else if (strcmp(opt, "-c") == 0) {
        (*i)++;
        data->str_count = av[*i];
    }
    else
        return (1);
    return (0);
}

static int search_opt(char **av, t_ping *data) {
    for (int i = 1; av[i]; i++) {
        if (data->hostname) {
            if (data->help)
                return (dispatch_err(HELP_ERR, NULL));
            return (dispatch_err(BAD_OP, NULL));
        }
        if (av[i][0] == '-') {
            if (check_opt(&i, av, av[i], data) == 1)
                return (dispatch_err(BAD_OPT, av[i]));
        }
        else
            data->hostname = av[i];
    }
    if (data->help && (data->verbose || data->str_count || data->hostname))
        return (dispatch_err(HELP_ERR, NULL));
    return (0);
}

static int parse_count(t_ping *data) {
    long    value;
    char    *end;

    errno = 0;
    value = strtol(data->str_count, &end, 10);
    if (*end != '\0')
        return (dispatch_err(INV_COUNT, NULL));
    if (errno == ERANGE || value > INT_MAX || value < 1)
        return (dispatch_err(INV_COUNT, NULL));
    data->count = (int)value;
    return (0);
}

int parser(char **av, t_ping *data) {
    if (search_opt(av, data) == 1)
        return (1);
    if (data->help)
        return(print_help(), 0);
    if (!data->hostname)
        return (dispatch_err(BAD_OP, NULL));
    if (data->str_count) {
        if (parse_count(data) == 1)
            return (1);
    }
    return (0);
}