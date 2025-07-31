#include "LoopLambda.h"

LoopLambda::LoopLambda(Config* config) :
    LambdaBase(config, LAMBDA_FOREACH),
    m_numIters(0),
    m_remainingIters(0)
{
}

LoopLambda::~LoopLambda(void)
{
}

bool LoopLambda::runLambda(void)
{
    // TODO: Optionally stop on error
    bool success = true;

    for (; m_remainingIters > 0; m_remainingIters--)
    {
        for (array<macroPtr_t, MAX_NUM_OF_MACROS>::const_iterator it = m_macros.cbegin(); it != m_macros.cend(); it++)
        {
            if (*it == nullptr)
            {
                break;
            }

            success &= (*it)();
        }
    }

    return success;
}

bool LoopLambda::undoLambda(void)
{
    return true;
}

bool LoopLambda::teardown(void)
{
    return false;
}

void LoopLambda::setNumIters(loopLambdaIter_t numIters)
{
    m_numIters = numIters;
}

void LoopLambda::reset(void)
{
    m_remainingIters = m_numIters;
}
