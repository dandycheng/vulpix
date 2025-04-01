#include "MacroBase.h"
#include "config.h"
#include "logs.h"

MacroBase::MacroBase(Config* config) :
    m_config(config)
{
}

MacroBase::~MacroBase(void)
{
}

bool MacroBase::runMacro(macroData_t data)
{
    return false;
}

bool MacroBase::undoMacro(macroData_t data)
{
    return false;
}