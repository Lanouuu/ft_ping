#include "ft_ping.h"

int main(int ac, char **av) {
    t_ping  data;

    if (ac == 1)
        return (dispatch_err(MISS_HOST_OP, NULL, 0));
    if (signals_handler() == 1)
        return (1);
    init_data(&data);
    if (parser(av, &data) == 1)
        return (1);
    if (data.help)
        return(0);
    if (resolve_host(&data) == 1)
        return (1);
    if (init_socket(&data) == 1)
        return (1);
    if (ping_pong(&data) == 1) {
        free_ping(&data);
        return (1);
    }
    display_stats(&data);
    free_ping(&data);
    return (0);
}
