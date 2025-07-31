#include "LambdaBase.h"
#include "config.h"
#include <cstring>

LambdaBase::LambdaBase(Config* config, lambda_t lambdaType) :
    m_config(config),
    m_numMacros(0),
    m_lambdaType(lambdaType)
{
    std::fill(m_macros.begin(), m_macros.end(), nullptr);
    std::fill(m_teardownMacros.begin(), m_teardownMacros.end(), nullptr);
}

LambdaBase::~LambdaBase(void)
{
    if (!teardown())
    {
        cerr << "Macros teardown unsuccessful!\n";
    }
}

bool LambdaBase::addMacro(macroPtr_t macro, macroPtr_t teardown)
{
    if ((macro != nullptr) && (m_numMacros < MAX_NUM_OF_MACROS - 1))
    {
        m_macros[m_numMacros] = macro;
        m_teardownMacros[m_numMacros] = teardown;
        m_numMacros++;

        return true;
    }

    return false;
}

bool LambdaBase::runLambda(void)
{
    return false;
}

bool LambdaBase::teardown(void)
{
    return false;
}

lambda_t LambdaBase::getLambdaType(void) const
{
    return m_lambdaType;
}

uint8_t LambdaBase::getNumMacros(void) const
{
    return m_numMacros;
}