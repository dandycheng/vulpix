#ifndef LAMBDA_BASE_H
#define LAMBDA_BASE_H

#include <stdint.h>
#include "MacroBase.h"
#include "config.h"

// TODO: Macro to define lambda type and check boundaries as well
// NOTE: Lambdas are like foreach, map, etc
typedef uint16_t lambda_t;    // Defines the type of lambda is being run (i.e.: What functionality is being run).

#define LAMBDA_FOREACH      0x0001
#define LAMBDA_NULL         0xFFFF

#define MAX_NUM_OF_MACROS    16


class LambdaBase
{
public:
    LambdaBase(Config* config);
    ~LambdaBase(void);

    bool addMacro(macro_t macro, macro_t teardown);
    bool teardown(void);
    virtual bool runLambda(void) = 0;
    virtual bool undoLambda(void) = 0;

private:
    macro_t* m_macros;
    macro_t* m_teardownMacros;
    uint8_t m_numMacros;
    Config* m_config;
};

#endif