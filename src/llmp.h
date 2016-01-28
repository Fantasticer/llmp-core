#ifndef _STP_H_
#define _STP_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct llmp_state LLMPState;

/* LLMP socket descriptor */
typedef int LLMPSocket;
typedef uint64_t MessageId;
typedef struct llmp_message {

} LLMPMessage;

// connections not initiated
typedef enum connection_op {
    DROP,
    REJECT,
    ACCEPT
} ConnectionOP;


typedef struct remote_id {
    char *address;
    uint16_t port;
    SessionKey *key;
} RemoteId;


LLMPState *llmp_open(uint16_t port);
void llmp_close(LLMPState *llmp);
void llmp_poll(LLMPState *llmp);

void llmp_add_authorized_remote(LLMPState *state, RemoteId id, SessionKey *key);
void llmp_remove_authorized_remote(LLMPState *state, RemoteId id);

// void llmp_set_incoming_connection_op(ConnectionOP op);


LLMPSocket llmp_accept(LLMPState *llmp);
LLMPSocket llmp_connect(LLMPState *llmp, char *remote, uint16_t port);
void llmp_disconnect(LLMPSocket socket);


void get_remote_ip_of(LLMPSocket socket);
void get_remote_port_of(LLMPSocket socket);

// pops a queue
MessageId llmp_last_message_ack(LLMPSocket socket);

void llmp_recv_message(LLMPState, LLMPMessage *msg);
void llmp_send_message(LLMPState *llmp, LLMPSocket *socket, LLMPMessage *msg);
void llmp_broadcast(LLMPState *llmp, LLMPMessage *msg);

#endif
