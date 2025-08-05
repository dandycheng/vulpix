#include "LambdaBase.h"
using namespace std;

typedef uint16_t MapLambdaIter_t;

class MapLambda : public LambdaBase
{
public:
    MapLambda(Config* config);
    ~MapLambda(void);

    virtual bool runLambda(macroData_t data, bool isUndo) override;
    virtual bool teardown(void) override;

    void setNumIters(MapLambdaIter_t numIters);
    void reset(void);

private:
    MapLambdaIter_t m_numIters;
    MapLambdaIter_t m_remainingIters;
};