#include "./http_c.h"

// sets port to passed port

void set_port(http* _http, int PORT) {
    _http->PORT = PORT;
}

// sets buffer size to passed buffer size

void set_buffer_size(http* _http, int BUFFER_SIZE) {
    _http->BUFFER_SIZE = BUFFER_SIZE;
}

// initiates our http server

void initiate_http(http* _http) {
    // Starting up winshock api

    if (WSAStartup(MAKEWORD(2,2), &_http->wsa_data) != 0) {
        WSA_ERROR("WSAStartup failed");
        R_EF;
    }

    // creating server socket, ipv4

    _http->server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_http->server_socket == INVALID_SOCKET) {
        WSA_ERROR("Socket creation failed");
        WSACleanup();
        R_EF;
    }

    // configuring server address

    _http->server_addr.sin_family = AF_INET;
    _http->server_addr.sin_addr.s_addr = INADDR_ANY;
    _http->server_addr.sin_port = htons(_http->PORT);

    // binding server address to server socket

    if (bind(_http->server_socket, (struct sockaddr *)&_http->server_addr, sizeof(_http->server_addr)) == SOCKET_ERROR) {
        WSA_ERROR("Bind failed");
        closesocket(_http->server_socket);
        WSACleanup();
        R_EF;
    }

    // listening to incoming connections

    if (listen(_http->server_socket, SOMAXCONN) == SOCKET_ERROR) {
        WSA_ERROR("Listen failed");
        closesocket(_http->server_socket);
        WSACleanup();
        R_EF;
    }
}

// accepts incoming connection
// if connection is success it returns 0
// else returns 2

int accept_connection(http* _http) {
    int client_addr_len = sizeof(_http->client_addr);

    _http->client_socket = accept(_http->server_socket, (struct sockaddr *)&_http->client_addr, &client_addr_len);
    if (_http->client_socket == INVALID_SOCKET) {
        WSA_ERROR("Accept failed");
        return 2;
    }

    return 0;
}

// handles incoming client's requests

void handle_client(http* _http) {
    char buffer[_http->BUFFER_SIZE];
    int bytes_received;

    bytes_received = recv(_http->client_socket, buffer, _http->BUFFER_SIZE - 1, 0);
    if (bytes_received == SOCKET_ERROR) {
        WSA_ERROR("recv failed");
        closesocket(_http->client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received request: \n%s\n", buffer);

    const char* response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 80\r\n"
            "\r\n"
            "<html><body><h1>Hello, World! Hello from the server</h1></body></html>";

    send(_http->client_socket, response, strlen(response), 0);
    closesocket(_http->client_socket);
}

// Closes our http server

void close_http(http* _http) {
    closesocket(_http->server_socket);
    WSACleanup();
}