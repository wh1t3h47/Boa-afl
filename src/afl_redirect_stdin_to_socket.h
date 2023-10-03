#ifndef AFL_REDIRECT_STDIN_TO_SOCKET_H
#define AFL_REDIRECT_STDIN_TO_SOCKET_H

// ssize_t
#include <unistd.h>
void redirect_stdin_to_socket(int server_s);

#endif // AFL_REDIRECT_STDIN_TO_SOCKET_H
