#include "MapLambda.h"

MapLambda::MapLambda(Config* config) :
    LambdaBase(config, LAMBDA_FOREACH),
    m_numIters(0),
    m_remainingIters(0)
{
}

MapLambda::~MapLambda(void)
{
}

bool MapLambda::runLambda(macroData_t data, bool isUndo)
{
    // TODO: Optionally stop on error
    bool success = true;

    array<macroPtr_t, MAX_NUM_OF_MACROS>::const_iterator it    { m_macros.cbegin() };
    array<macroPtr_t, MAX_NUM_OF_MACROS>::const_iterator itEnd { m_macros.cend()   };

    if (isUndo)
    {
        it = m_undoMacros.cbegin();
        itEnd = m_undoMacros.cend();
    }

    for (; m_remainingIters > 0; m_remainingIters--)
    {
        for (; it != itEnd; it++)
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

bool MapLambda::teardown(void)
{
    return false;
}

void MapLambda::setNumIters(MapLambdaIter_t numIters)
{
    m_numIters = numIters;
}

void MapLambda::reset(void)
{
    m_remainingIters = m_numIters;
}
