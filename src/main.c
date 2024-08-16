#include "../includes/http_c.h"

int main(int argc, char** argv) {
    http server;

    set_port(&server, 8080);
    set_buffer_size(&server, 1024);

    initiate_http(&server);

    while (1) {
        if (accept_connection(&server) != 0) continue;

        handle_client(&server);
    }

    close_http(&server);

    return 0;
}
