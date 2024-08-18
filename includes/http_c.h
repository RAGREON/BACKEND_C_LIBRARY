#ifndef HTTP_C
#define HTTP_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "api.h"
#include "response.h"

#pragma comment(lib, "ws2_32.lib")

// Custom macros to reduce code

#define R_EF exit(EXIT_FAILURE) 
#define WSA_ERROR(string) printf("%s: %d\n", string, WSAGetLastError());

// http strcture
// this is what will be reponsible for doing everything 
// high level abstraction 

typedef struct {
    int                 PORT;
    int                 BUFFER_SIZE;

    WSADATA             wsa_data;
    SOCKET              server_socket, client_socket;

    struct sockaddr_in  server_addr, client_addr;
} http;

// sets port to passed port

void set_port(http* _http, int PORT);

// sets buffer size to passed buffer size

void set_buffer_size(http* _http, int BUFFER_SIZE);

// initiates our http server

void initiate_http(http* _http);

// accepts incoming connection
// if connection is success it returns 0
// else returns 2

int accept_connection(http* _http);

// handles incoming client's requests

void handle_client(http* _http);

// Closes our http server

void close_http(http* _http);

#endif