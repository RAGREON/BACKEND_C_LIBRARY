#include "./api.h"
#include <stdio.h>

int main(int argc, char** argv) {
    api* newAPI = create_api("/about", POST);


    printf("route -> %s\nmethod -> %d\n", newAPI->route, newAPI->method);


    return 0;
}