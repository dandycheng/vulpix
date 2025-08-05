#include "LambdaBase.h"
#include "config.h"
#include <cstring>

LambdaBase::LambdaBase(Config* config, lambda_t lambdaType) :
    m_config(config),
    m_numMacros(0),
    m_lambdaType(lambdaType)
{
    std::fill(m_macros.begin(), m_macros.end(), nullptr);
    std::fill(m_undoMacros.begin(), m_undoMacros.end(), nullptr);
}

LambdaBase::~LambdaBase(void)
{
    if (!teardown())
    {
        cerr << "Macros teardown unsuccessful!\n";
    }
}

bool LambdaBase::addMacro(macroPtr_t macro, macroPtr_t undoMacro)
{
    if ((macro != nullptr) && (m_numMacros < MAX_NUM_OF_MACROS - 1))
    {
        m_macros[m_numMacros] = macro;
        m_undoMacros[m_numMacros] = undoMacro;
        m_numMacros++;

        return true;
    }

    return false;
}

bool LambdaBase::runLambda(macroData_t data, bool isUndo)
{
    return false;
}

bool LambdaBase::teardown(void)
{
    return true;
}

lambda_t LambdaBase::getLambdaType(void) const
{
    return m_lambdaType;
}

uint8_t LambdaBase::getNumMacros(void) const
{
    return m_numMacros;
}