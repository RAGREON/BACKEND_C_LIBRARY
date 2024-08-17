#include "./response.h"
#include <stdlib.h>
#include <string.h>

response* create_response(int status_code, const char* content_type, const char* content) {
    response* _response = (response*)malloc(sizeof(response));

    _response->status_code = status_code;
    _response->content_type = content_type;
    _response->content = content;
    _response->content_length = strlen(content);

    return _response;
}