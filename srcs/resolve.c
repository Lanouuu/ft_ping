#include "ft_ping.h"

int resolve_host(t_ping *data) {
    struct addrinfo hints;
    struct addrinfo *result;
    int             ret;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    ret = getaddrinfo(data->hostname, NULL, &hints, &result);
    if (ret != 0)
        return (dispatch_err(GAI_ERR, data->hostname, ret));
    memcpy(&data->addr, result->ai_addr, sizeof(data->addr));
    freeaddrinfo(result);
    return (0);
}