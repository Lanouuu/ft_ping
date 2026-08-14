#include "ft_ping.h"

int main(int ac, char **av) {
    t_ping  data;

    if (ac == 1)
        return (dispatch_err(MISS_HOST_OP, NULL, 0));
    init_data(&data);
    if (parser(av, &data) == 1)
        return (1);
    if (data.help)
        return(0);
    if (resolve_host(&data) == 1)
        return (1);
   // printf("%s\n", inet_ntoa(data.addr.sin_addr));
    if (init_socket(&data) == 1)
        return (1);
    if (ping_pong(&data) == 1)
        return (1);
    return (0);
}
