#include "ft_ping.h"

static int  ping_loop(t_ping *data) {
    int ret_send;

    ret_send = 0;
    errno = 0;
    make_packet(data);
    // clock start
    ret_send = sendto(
                data->sockfd,
                data->packet,
                sizeof(data->packet),
                0,
                (struct sockaddr *)&data->addr,
                sizeof(data->addr)
    );
    if (ret_send == -1)
        return (dispatch_err(SEND_ERR, NULL, errno));
    // recvfrom
    // wait et clock stop
    return (0);
}

static int  ping_count(t_ping *data) {
    
    return (0);
}

int ping_pong(t_ping *data) {
    if (data->count) {
        while (data->count > 0) {
            if (ping_count(data) == 1)
                return (1);
        }
    }
    else {
        while (1) {
            if (ping_loop(data) == 1)
                return (1);
        }
    }
    return (0);
}