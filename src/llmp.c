#include "llmp.h"


struct llmp_state {
    uint32_t connection_count;

    uint32_t sequence_clock;
};


typedef enum socket_state {
    LISTEN,
    SYN_SENT,
    SYN_RECIEVED,
    ESTABLISHED,
    CLOSED,
    TIME_WAIT
} SocketState;


typedef struct socket {
    SocketState state;
    uint32_t isn;
    uint32_t seq;
    uint32_t ack;

    // remote ip
    // remote port
    // local port
} Socket;


typedef struct llmp_header {
    uint16_t seq;
    uint16_t ack;
    uint16_t flags;
    uint16_t msg_id;
    uint16_t frags;
    uint16_t frag_num;
    uint8_t  checksum[16];
} LLMPHeader;


LLMPState llmp_open(uint16_t port)
{
    if (port == 0) {
        //
        return;
    }
}


void llmp_close(LLMPSocket socket)
{

}


void llmp_poll(LLMPState *state)
{

}


LLMPSocket llmp_accept(LLMPState *state)
{

}


LLMPSocket llmp_connect(LLMPState *state, char *address, uint16_t port)
{

}


void llmp_disconnect(LLMPSocket socket)
{

}


void get_remote_ip_of(LLMPSocket socket)
{

}


void get_remote_port_of(LLMPSocket socket)
{

}


uint16_t llmp_last_message_ack(LLMPSocket socket)
{

}


void llmp_recv_message(LLMPState, LLMPMessage *msg)
{

}


void llmp_send_message(LLMPState *llmp, LLMPSocket *socket, LLMPMessage *msg)
{

}


void llmp_broadcast(LLMPState *llmp, LLMPMessage *msg)
{

}
