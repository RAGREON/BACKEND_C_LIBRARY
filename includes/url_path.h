#ifndef URL_PATH
#define URL_PATH

// Enum to specify the request method

typedef enum {
    GET,
    POST,
    HEAD
} METHOD;

// api will hold route and method
// it will be used alongside with response

typedef struct {
    const char*     route;
    METHOD          method;
} api;

#endif