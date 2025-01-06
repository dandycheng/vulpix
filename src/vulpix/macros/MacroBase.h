#ifndef MACRO_BASE_H
#define MACRO_BASE_H

class Config;

typedef bool (*macro_t)(void);

class MacroBase
{
public:
    MacroBase(Config* config);
    ~MacroBase(void);

    virtual bool runMacro(void) = 0;
    virtual bool undoMacro(void) = 0;

protected:
    Config* m_config;
};

#endif