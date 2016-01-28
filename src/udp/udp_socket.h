/**
 * Cross-platform interface to the UDP socket
 */

#ifndef __UDP_SOCKET_H__
#define __UDP_SOCKET_H__

#include <stdbool.h>
#include <stdint.h>
#include <netinet/in.h>
#include <stdbool.h>


typedef enum udpstat_e {
    OK                = 0,
    ERR_SOCKET_ACCESS = 1,
    ERR_AF_UNSOPORTED = 2,
    ERR_ALLOC         = 3,
    ERR_UNSPECIFIED   = 4;
} UDPstat;


typedef struct udp_socket UDP_Socket;


typedef struct udp_packet {
    /* Remote address - packet origin or destination depending
       on whether the packet is being sent or received. */
    char *address;

    /** Remote port to which the packet is sent. */
    uint16_t port;

    /** Packet data buffer. */
    void *data;

    /** Data length. */
    size_t length;

    /** Number of bytes that was actually transmitted. */
    int bytes_transmitted;
} UDP_Packet;


UDPstat  udp_socket_open         (UDP_Socket **s, bool inet6);
void     udp_socket_close        (UDP_Socket *s);
int      udp_socket_bind         (UDP_Socket *s, uint16_t local_port);
void     udp_socket_unbind       (UDP_Socket *s);
void     udp_socket_send_packet  (UDP_Socket *s, UDP_Packet *p);
void     udp_socket_send_packets (UDP_Socket *s, UDP_Packet **ps, npack);
int      udp_socket_recv         (UDP_Socket *s, UDP_Packet *p);
int      udp_socket_recv_packets (UDP_Socket *s, UDP_Packets **ps);
void     udp_socket_domain       (UDP_Socket *s);

#endif
