#include "ft_ping.h"

ssize_t receiver(t_ping *data) {
    ssize_t ret;

    ret = 0;
    errno = 0;
    if (ret == -1)
        return (dispatch_err(REC_ERR, NULL, errno));
    return (0);
}