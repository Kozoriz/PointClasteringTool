#include <memory>
#include <thread>

#include "../DataMeneger/DataMeneger.hpp"
#include "../UI/Render.hpp"

class LifeCycle
{
public:
    LifeCycle( );
    void init( );
    void start( );
    void stop( );

private:
    // Module
    DataMeneger dataMeneger;
    Render render;
};
