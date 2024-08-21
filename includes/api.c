#include "api.h"
#include <stdlib.h>

api* create_api(const char* _route, METHOD _method) {
    api* _api = (api*)malloc(sizeof(api));

    _api->route = _route;
    _api->method = _method;

    return _api;
}