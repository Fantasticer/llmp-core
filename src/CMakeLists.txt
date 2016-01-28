
add_library(foonet STATIC UDP/udp_socket.h UDP/udp_socket_posix.c)

set_target_properties(foonet PROPERTIES LINKER_LANGUAGE C)
