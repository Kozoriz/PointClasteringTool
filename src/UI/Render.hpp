#include <memory>

class RenderImpl;

class Render
{
public:
    void start_app( );
    bool render_cloude( );
    void operator( )( );

    std::shared_ptr< RenderImpl > mImpl;
};
