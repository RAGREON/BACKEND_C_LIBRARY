#include "../includes/response.h"
#include <stdio.h>

int main(int argc, char** argv) {
    response* newResponse = create_response(
        200,
        "text/html",
        "hello"
    );

    printf("status code: %d\ncontent-type: %s\ncontent: %s", newResponse->status_code, newResponse->content_type, newResponse->content);

    return 0;
}