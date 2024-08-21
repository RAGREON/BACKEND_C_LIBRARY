#ifndef RESPONSE
#define RESPONSE

// structure called reponse to hold our response information
// structure contains: status_code, content_type, content_length, and content
// this structure only contains meta-data of the reponse
// will need to be parsed later through a function

typedef struct {
    int             status_code;
    const char*     content_type;
    int             content_length;
    const char*     content;
} response;

// will return a pointer to a response structure

response* create_response(int status_code, const char* content_type, const char* content);

#endif