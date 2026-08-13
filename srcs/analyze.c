#include "ft_ping.h"

int analyzer(t_ping *data, const unsigned char *buf, ssize_t len) {
    if (len < sizeof(struct iphdr))
        return (1);
    return (0);
}