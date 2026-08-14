#ifndef FT_PING
# define FT_PING

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>

# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h> //paquet ICMP
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

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
};

// typedef struct s_stats {

// } t_stats;

typedef struct s_display {
    ssize_t     len;
    char        ip[INET6_ADDRSTRLEN];
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

    // ICMP packets
    unsigned char       packet[64];
    uint16_t            packet_id;
    uint16_t            sequence;

    struct timespec      send_time;
    struct timespec      receive_time;

    t_display           display;
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
void		display_packet(t_display *display);

#endif
