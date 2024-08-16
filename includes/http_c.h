#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

// Custom macros to reduce code

#define R_EF exit(EXIT_FAILURE) 
#define WSA_ERROR(string) printf("%s: %d\n", string, WSAGetLastError());

// http strcture
// this is what will be reponsible for doing everything 
// high level abstraction 

typedef struct {
    int PORT;
    int BUFFER_SIZE;

    WSADATA wsa_data;
    SOCKET server_socket;

    struct sockaddr_in server_addr;
} http;

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