#include "ft_ping.h"

static double   compute_loss(t_ping *data) {
    double  loss;
    if (data->stats.sended == 0)
        return (0);
    loss = ((data->stats.sended - data->stats.received) * 100.0)
            / data->stats.sended;
    return (loss);
}

static double   compute_time(t_ping *data) {
    double time;

    time = (data->stats.end.tv_sec - data->stats.start.tv_sec)
            * 1000.0
            + (data->stats.end.tv_nsec - data->stats.start.tv_nsec)
            / 1000000.0;
    return (time);
}

static double   compute_mdev(t_ping *data) {
    double  mdev;

    if (data->stats.received == 0)
        return (0);
    mdev = sqrt(
        data->stats.rtt_squared / data->stats.received
        - data->stats.rtt_avg * data->stats.rtt_avg
    );
    return (mdev);
}

void    display_stats(t_ping *data) {
    data->stats.loss = compute_loss(data);
    data->stats.total_time = compute_time(data);
    data->stats.rtt_mdev = compute_mdev(data);
    fprintf(
        stdout,
        "--- %s ft_ping statistics ---\n",
        data->hostname
    );
    fprintf(
        stdout,
        "%d packets transmitted, %d received, %.1f%% packet loss, time %.0fms\n",
        data->stats.sended,
        data->stats.received,
        data->stats.loss,
        data->stats.total_time
    );
    fprintf(
        stdout,
        "rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
        data->stats.rtt_min,
        data->stats.rtt_avg,
        data->stats.rtt_max,
        data->stats.rtt_mdev
    );
    return ;
}
