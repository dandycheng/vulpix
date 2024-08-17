#ifndef DEBUG_H
#define DEBUG_H

#include <string>

using namespace std;

typedef enum errorCode
{
    ERR_INVALID_CONFIG,
    ERR_UNEXPECTED_BEHAVIOR
} errorCode_t;

#define LOG_DEBUG   "DEBUG"
#define LOG_ERROR   "ERROR"

#ifdef DEBUG
#define DEBUG_LOG(type, message, ...)   printf("%s() [" type "] " message "\n", __FUNCTION__, __VA_ARGS__)
#else
#define DEBUG_LOG(type, message, ...)   if (type == LOG_ERROR) printf("An error has occured: %s\n", message);
#endif

#endif