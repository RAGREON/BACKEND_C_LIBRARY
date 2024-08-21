#include "api_response.h"

void set_api(api_response* _api_response, const char* _route, METHOD _method) {
    _api_response->_api = create_api(_route, _method);
}   

void set_response(api_response* _api_response, int _status_code, const char* _content_type, const char* _content) {
    _api_response->_response = create_response(_status_code, _content_type, _content);
}