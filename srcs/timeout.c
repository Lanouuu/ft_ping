#include "ft_ping.h"

int  refresh_timeout(t_ping *data) {
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now) == -1)
            return (dispatch_err(CLOCK_ERR, NULL, errno));
    if (now.tv_sec > data->deadline.tv_sec
        || (now.tv_sec == data->deadline.tv_sec
            && now.tv_nsec >= data->deadline.tv_nsec))
    {
        data->timeout.tv_sec = 0;
        data->timeout.tv_usec = 0;
        return (0);
    }
    data->timeout.tv_sec = data->deadline.tv_sec - now.tv_sec;
    if (data->deadline.tv_nsec < now.tv_nsec) {
        data->timeout.tv_sec--;
        data->timeout.tv_usec = 
            (data->deadline.tv_nsec + 1000000000L - now.tv_nsec)
            / 1000;
    }
    else {
        data->timeout.tv_usec = 
            (data->deadline.tv_nsec - now.tv_nsec)
            / 1000;
    }
    return (0);
}
