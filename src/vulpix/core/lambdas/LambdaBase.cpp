#include "LambdaBase.h"
#include "config.h"
#include <cstring>

LambdaBase::LambdaBase(Config* config) :
    m_config(config),
    m_macros(new macro_t[MAX_NUM_OF_MACROS]),
    m_teardownMacros(new macro_t[MAX_NUM_OF_MACROS]),
    m_numMacros(0)
{
    memset(m_macros, 0, sizeof(m_macros));
}

LambdaBase::~LambdaBase(void)
{
    if (!teardown())
    {
        cout << "Macros teardown unsuccessful!\n";
    }

    delete m_macros;
}

bool LambdaBase::addMacro(macro_t macro, macro_t teardown)
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
    bool success = true;

    for (uint8_t i = 0; i < m_numMacros; i++)
    {
        success &= m_macros[i]();
    }

    return success;
}

bool LambdaBase::teardown(void)
{
    bool success = true;

    for (uint8_t i = 0; i < m_numMacros; i++)
    {
        if (m_teardownMacros[i] != nullptr)
        {
            success &= m_teardownMacros[i]();
        }
    }

    return success;
}