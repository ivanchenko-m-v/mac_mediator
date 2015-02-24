/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-09-2013
///		Date update	: 06-10-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QMessageBox>
#include <QTranslator>
#include <stdexcept>

#include "app_mac_mediator.h"
#include "business_logic.h"

namespace mac_mediator
{
		bool app_mac_mediator::_is_logic_initialized = false;
//#############################################################################
//			class app_mac_mediator
//#############################################################################
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================

	///-------------------------------------------------------------------------
	///	app_mac_mediator( int & argc, char ** argv )
	///
	app_mac_mediator::app_mac_mediator( int & argc, char ** argv ) :
		QApplication( argc, argv )
	{
		this->initialize( );
	}


	///------------------------------------------------------------------------
	///	~app_mac_mediator( )
	///
	app_mac_mediator::~app_mac_mediator( )
	{
		this->closeAllWindows( );

         //close all threads
		if( app_mac_mediator::_is_logic_initialized )
		{
			the_business_logic( ).exit( );
		}

		qDebug( ) << "application object destroyed correctly";
	}

	//=========================================================================
	//		PROPERTIES
	//=========================================================================

	//=========================================================================
	//		OPERATORS
	//=========================================================================

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	///------------------------------------------------------------------------
	///	the_business_logic( )
	///
	business_logic& app_mac_mediator::the_business_logic( )
	{
		static business_logic logic;

		if( !app_mac_mediator::_is_logic_initialized )
		{
			app_mac_mediator::_is_logic_initialized = true;
			//init logic dynamic memory allocated objects
			logic.init( );
		}
		return logic;
	}

	/// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
	void app_mac_mediator::initialize( )
	{
		try
		{
            this->_translator.load(
							"russian.lng",
							QApplication::applicationDirPath( )
						   );
			//translation
			this->installTranslator( &( this->_translator ) );
			this->setWindowIcon(
							*( new QIcon( ":/image/images/mac_logo.png" ) )
							   );
			//this->init_database( );
		}
		catch( std::exception &ex )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "app init error" ),
									QString::fromUtf8( ex.what( ) )
								  );
		}
		catch( ... )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "critical" ),
									QObject::tr(
												"unexpected error while "
												"program initializing"
												)
								  );
		}
	}

    ///------------------------------------------------------------------------
	///	load_translation( )
	///
    void app_mac_mediator::load_translation( )
    {
        this->_translator.load(
                        "russian.lng",
                        QApplication::applicationDirPath( )
                       );
        //translation
        this->installTranslator( &( this->_translator ) );
    }

	///------------------------------------------------------------------------
	///	parse_cfg_file( )
	///
	void app_mac_mediator::parse_cfg_file( )
	{
		QFile fcfg(
					QApplication::applicationDirPath( ) +
					"/app_mac_mediator.cfg"
				  );
		fcfg.open( QIODevice::ReadOnly );
		//connect file to stream
		QTextStream stream( &fcfg );
		stream.setCodec( "UTF-8" );

		qDebug( ) << "parsing db connection params...\n";
		while( !stream.atEnd( ) )
		{
			QString s_line = stream.readLine( );
                        if( s_line.indexOf( QRegExp( "[A-Za-z(),:#\\/]+" ) ) < 0 )
			{
				continue;
			}
                        QStringList list_params = s_line.split( "#:#" );
                        /*
			if( list_params.count( ) > 1 )
			{
				QString s_param( list_params.at( 0 ) ),
						s_value( list_params.at( 1 ) );
				qDebug( ) << s_param << ":" << s_value;
				if( s_param == "db_provider" )
				{
					this->_cnn_props._x_provider = s_value.toStdString( );
				}
				if( s_param == "db_database" )
				{
					this->_cnn_props._x_database = s_value.toStdString( );
				}
				if( s_param == "db_host" )
				{
					this->_cnn_props._x_host = s_value.toStdString( );
				}
				if( s_param == "db_port" )
				{
					this->_cnn_props._n_port = s_value.toInt( );
				}
				if( s_param == "db_user" )
				{
					this->_cnn_props._x_user = s_value.toStdString( );
				}
				if( s_param == "db_pwd" )
				{
					this->_cnn_props._x_pwd = s_value.toStdString( );
				}
			}
                */
		}
		fcfg.close( );
	}

	//=========================================================================
	//		SLOTS
	//=========================================================================

//#############################################################################

}//namespace mac_mediator
