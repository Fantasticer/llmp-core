#include "udp_socket.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>


struct udp_socket {
    int fd;
    int domain;
    union local_addr {
        struct sockaddr_in6 inet6;
        struct sockaddr_in  inet4;
    };
};


UDPStat udp_socket_open(UDP_Socket **s, bool inet6)
{
    *s = malloc(sizeof(UDP_Socket));

    if (!*s)
        return ERR_ALLOC;

    if (inet6) {
        s->fd = socket(AF_INET6, SOCK_DGRAM, 0);
        s->domain = AF_INET6;
    } else {
        s->fd = socket(AF_INET, SOCK_DGRAM, 0);
        s->domain = AF_INET;
    }
    if (s->fd == -1) {
        int e = errno;
        free(s);
        switch (e) {
        case EACCES: return ERR_SOCKET_ACCES;
        case EAFNOSUPPORT: return ERR_AF_UNSUPPORTED;
        case ENOBUFS:
        case ENOMEM: return ERR_ALLOC;
        default: return ERR_UNSPECIFIED;
        }
    }
    return OK;
}


void udp_socket_close(UDP_Socket *s)
{
    close(s->fd);
}


static int bind_inet4(UDP_Socket *s, uint16_t port)
{
    memset(&(s->local_addr.inet4), 0, sizeof(struct sockaddr_in));

    s->local_addr.sin_family      = s->domain;
    s->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s->local_addr.sin_port        = htons(local_port);

    if (bind(s->fd, (struct sockaddr*) &(s->local_addr), sizeof(struct sockaddr_in)) < 0)
        return -1;

    return 0;
}


static int bind_inet6(UDP_Socket *s, uint16_t port)
{

}


int udp_socket_bind(UDP_Socket *s, uint16_t local_port)
{
    if (s->domain == AF_INET)
        bind_inet4(s, local_port);
    else
        bind_inet6(s, local_port);

    return 0;
}


static void send_inet4(UDP_Socket *s, UDP_Packet *p)
{
    struct sockaddr_in remote;

    memset((char*) &remote, 0, sizeof(remote));

    remote.sin_family = s->domain;
    remote.sin_port   = htons(p->port);

    if (inet_aton(p->address, &remote.sin_addr) == 0) {
        // some error
        return;
    }
    int t = sendto(s->fd,
                   p->data,
                   p->length,
                   0,
                   (struct sockaddr*) &remote,
                   sizeof(struct sockaddr_in));

    p->bytes_transmitted = t;
}


static void send_inet6(UDP_Socket *s, UDP_Packet *p)
{
    struct sockaddr_in6 remote;

    memset((char*) &remote, 0, sizeof(remote));

    remote.sin6_family = s->domain;
    remote.sin6_port   = htons(p->port);

    if (inet_pton(AF_INET6, p->address, &remote.sin6_addr) == 0)
        return;
}


void udp_socket_send(UDP_Socket *s, UDP_Packet *p)
{
    if (s->domain == AF_INET)
        send_inet4(s, p);
    else
        send_inet6(s, p);
}


static void recv_inet4(UDP_Socket *s, UDP_Packet *p)
{

}


static void recv_inet6(UDP_Socket *s, UDP_Packet *p)
{

}


int udp_socket_recv(UDP_Socket *s, UDP_Packet *p)
{
    if (s->domain == AF_INET)
        return recv_inet4(s, p);

    return recv_inet6(s, p);
}


int udp_socket_domain(UDP_Socket *s)
{
    return s->domain;
}
