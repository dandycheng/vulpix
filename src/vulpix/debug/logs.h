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

#define LOG_BOOL_TO_YES_NO(val)      val ? "Yes" : "No"

#ifdef DEBUG
#define DEBUG_LOG(type, message, ...)   printf("%s [%s:%d - %s()] " message "\n", type, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ERROR_LOG(message, ...)
#else
#define DEBUG_LOG(type, message, ...)
#define ERROR_LOG(message, ...)         printf("ERROR [%s:%d - %s()] " message "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

#endif