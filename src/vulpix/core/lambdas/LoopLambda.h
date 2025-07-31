#include "LambdaBase.h"
using namespace std;

typedef uint16_t loopLambdaIter_t;

class LoopLambda : public LambdaBase
{
public:
    LoopLambda(Config* config);
    ~LoopLambda(void);

    virtual bool runLambda(void);
    virtual bool undoLambda(void);
    virtual bool teardown(void);

    void setNumIters(loopLambdaIter_t numIters);
    void reset(void);

private:
    loopLambdaIter_t m_numIters;
    loopLambdaIter_t m_remainingIters;
};