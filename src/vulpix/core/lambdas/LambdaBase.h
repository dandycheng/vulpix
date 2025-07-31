#ifndef LAMBDA_BASE_H
#define LAMBDA_BASE_H

#include <stdint.h>
#include <array>
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
    LambdaBase(Config* config, lambda_t lambdaType);
    ~LambdaBase(void);
    bool addMacro(macroPtr_t macro, macroPtr_t teardown);
    lambda_t getLambdaType(void) const;
    uint8_t getNumMacros(void) const;

    virtual bool runLambda(void)  = 0;
    virtual bool undoLambda(void) = 0;
    virtual bool teardown(void)   = 0;

private:
    lambda_t m_lambdaType;
    uint8_t m_numMacros;
    Config* m_config;

protected:
    std::array<macroPtr_t, MAX_NUM_OF_MACROS> m_macros;
    std::array<macroPtr_t, MAX_NUM_OF_MACROS> m_teardownMacros;
};

#endif