#include <memory>

class RenderImpl;

class Render
{
public:
    void start_app( );
    void operator( )( );

    std::shared_ptr< RenderImpl > mImpl;
};
