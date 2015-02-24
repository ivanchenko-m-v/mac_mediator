/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-09-2013
///		Date update	: 18-12-2013
///		Comment		:
/// ============================================================================
#include "application.h"
#include "main_window.h"

/// ----------------------------------------------------------------------------
///	main( int argc, char *argv[] )
/// ----------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
	mac_mediator::application app( argc, argv );

    app.authorize( );
    if( !app.authorized_mediator( ).mediator( ).length( ) )
    {
        app.exit( -1 );
        return -1;
    }
	mac_mediator::main_window w;
    w.append_title_text( app.authorized_mediator( ).mediator( ) );
    w.show( );

    return app.exec( );
}
