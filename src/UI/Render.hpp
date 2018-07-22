#include <memory>

namespace common {
class AppointeeImpl;
}
class RenderImpl;

class Render
{
public:
    void start_app( );
    bool render_cloude( );
    void operator( )( );

private:
    friend class common::AppointeeImpl;
    std::shared_ptr< RenderImpl > mImpl;
};
