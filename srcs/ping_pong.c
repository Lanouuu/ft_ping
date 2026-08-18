#include "ft_ping.h"

static int  ping_loop(t_ping *data) {
    int             ret;
    int             ret_recv;
    

    make_packet(data);
    if (sender(data) == 1)
        return (1);
    while (1) {
        errno = 0;
        FD_ZERO(&data->fds);
        FD_SET(data->sockfd, &data->fds);
        if (refresh_timeout(data) == 1)
            return (1);
        ret = select(
            data->sockfd + 1,
            &data->fds,
            NULL,
            NULL,
            &data->timeout
        );
        if (ret == -1 && errno == EINTR)
            continue ;
        if (ret == -1)
            return (dispatch_err(SEL_ERR, NULL, errno));
        if (ret > 0) {
            ret_recv = receiver(data);
            if (ret_recv == 1)
                return (1);
            else if (ret_recv == 2)
                continue ;
        }
        else if (ret == 0)
            data->sequence++;
        break ;
    }
    return (0);
}

int ping_pong(t_ping *data) {
    fprintf(
            stdout, 
            "PING %s (%s) 56(84) bytes of data.\n",
            data->hostname,
            inet_ntoa(data->addr.sin_addr)
    );
    if (data->count) {
        while (data->count > 0) {
            if (ping_loop(data) == 1)
                return (1);
            data->count--;
        }
    }
    else {
        while (1) {
            if (ping_loop(data) == 1)
                return (1);
            sleep(1);
        }
    }
    return (0);
}
