#include "ft_ping.h"

int main(int ac, char **av) {
    t_ping  data;

    if (ac == 1)
        return (dispatch_err(MISS_HOST_OP, NULL));
    init_data(&data);
    if (parser(av, &data) == 1)
        return (1);
    if (data.help)
        return(0);
    return (0);
}