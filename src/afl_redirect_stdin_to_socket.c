#include "afl_redirect_stdin_to_socket.h"

void redirect_stdin_to_socket(int server_s)
{
    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
    {
        ssize_t bytesWritten = write(server_s, buffer, bytesRead);
        if (bytesWritten <= 0)
        {
            // Se a escrita falhou, encerre o servidor
            printf("FALHOU NA LEITURA - WRAPPER DO AFL");
            close(server_s);
            exit(0);
        }

        // Simule uma solicitação HTTP
        process_requests(server_s);
    }

    // Se a leitura falhou ou chegou ao fim do arquivo, encerre o servidor
    close(server_s);
    exit(0);
}
