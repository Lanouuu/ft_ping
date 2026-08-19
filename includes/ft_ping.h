#ifndef FT_PING
# define FT_PING

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <signal.h>

# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h> //paquet ICMP
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

extern volatile sig_atomic_t stop;

enum errors {
    MISS_HOST_OP,
    TOO_MUCH_OP,
    BAD_OP,
    BAD_OPT,
    HELP_ERR,
    INV_COUNT,
    GAI_ERR,
    SOCK_ERR,
    SEND_ERR,
    REC_ERR,
    CLOCK_ERR,
    SEL_ERR,
    SIG_SET,
    SIG_ACT,
};

typedef struct s_stats {
    int             sended;
    int             received;
    double          loss;

    struct timespec start;
    struct timespec end;
    double          total_time;
    double          rtt_max;
    double          rtt_min;
    double          rtt_avg;
    double          rtt_squared;
    double          rtt_mdev;
} t_stats;

typedef struct s_display {
    ssize_t     len;
    char        ip[INET_ADDRSTRLEN];
    uint16_t    sequence;
    uint8_t     ttl;
    double      time;
} t_display;

typedef struct s_ping {
    // options
    int                 verbose;
    int                 help;
    char                *str_count;
    int                 count;

    // sockets
    char                *hostname;
    struct sockaddr_in  addr;
    int                 sockfd;
    fd_set              fds;
    struct timeval      timeout;

    // ICMP packets
    unsigned char       packet[64];
    uint16_t            packet_id;
    uint16_t            sequence;

    struct timespec     send_time;
    struct timespec     receive_time;
    struct timespec     deadline;

    t_display           display;
    t_stats             stats;
} t_ping;

int         dispatch_err(int err, char *s, int ret);
void        print_help(void);

void        init_data(t_ping *data);
int         parser(char **av, t_ping *data);
int         resolve_host(t_ping *data);
int         init_socket(t_ping *data);

void        make_packet(t_ping *data);
uint16_t    checksum(const unsigned char *packet, size_t size);
int         ping_pong(t_ping *data);
ssize_t     sender(t_ping *data);
ssize_t     receiver(t_ping *data);
int         analyzer(t_ping *data, const unsigned char *buf, ssize_t len);
int         refresh_timeout(t_ping *data);
void		display_packet(t_display *display);
void        verbose(const unsigned char *buf, struct iphdr *ip_hdr, struct icmphdr *icmp_hdr, ssize_t len);

int         signals_handler(void);

void        display_stats(t_ping *data);

void        free_ping(t_ping *data);

#endif
