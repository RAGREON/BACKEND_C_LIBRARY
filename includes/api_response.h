#ifndef API_RESPONSE
#define API_RESPONSE

#include "api.h"
#include "response.h"

// structure to map our api with our response
// contains a pointer to api
// contains a pointer to response

typedef struct {
    api*         _api;
    response*    _response;
} api_response;

// sets the api of api_response 

void set_api(api_response* _api_response, const char* _route, METHOD _method);

// sets the response of api_response

void set_response(api_response* _api_response, int _status_code, const char* _content_type, const char* _content);

#endif