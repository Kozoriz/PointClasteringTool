#include "Render.hpp"
#include "impl/RenderImpl.hpp"

void
Render::start_app( )
{
    mImpl->qml_registration( );
    mImpl->start_app( );
}

bool
Render::render_cloude( )
{
}

void
Render::operator( )( )
{
}