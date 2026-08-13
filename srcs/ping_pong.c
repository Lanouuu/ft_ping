#include "ft_ping.h"

static int  ping_loop(t_ping *data) {
    make_packet(data);
    // clock start
    if (sender(data) == 1)
        return (1);
    if (receiver(data) == 1)
        return (1);
    // wait et clock stop
    return (0);
}

int ping_pong(t_ping *data) {
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
        }
    }
    return (0);
}