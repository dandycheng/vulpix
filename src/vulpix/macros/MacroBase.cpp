#include "MacroBase.h"
#include "config.h"

MacroBase::MacroBase(Config* config) :
    m_config(config)
{
}

MacroBase::~MacroBase(void)
{
}

bool MacroBase::runMacro(void)
{
    return false;
}

bool MacroBase::undoMacro(void)
{
    return false;
}