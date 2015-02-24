/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 11-10-2013
///		Comment		:
/// ============================================================================
#include <QFile>
#include <QRegExp>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include "application_params.h"

namespace espira
{

namespace utils
{
/// ############################################################################
///			class application_params
/// ############################################################################

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// parse_file( const QString &f_path )
    /// ------------------------------------------------------------------------
    void application_params::parse_cfg_file( const QString &f_path )
    {
        this->_hash_params.clear( );

        if( f_path.length( ) )
        {
            this->_f_path = f_path;
        }
		QFile fcfg( this->_f_path );
		if( !fcfg.exists( ) )
		{
    		qDebug( ) << this->_f_path << " file not exists\n";
    		return;
		}
		fcfg.open( QIODevice::ReadOnly );
		//connect file to stream
		QTextStream stream( &fcfg );
		stream.setCodec( "UTF-8" );

		qDebug( ) << "parsing cfg-file...\n";
		while( !stream.atEnd( ) )
		{
			QString s_line = stream.readLine( );
            if( s_line.indexOf( QRegExp( "[A-Za-z(),:#\\/]+" ) ) < 0 )
			{
				continue;
			}
            QStringList list_params = s_line.split( "#:#" );

			if( list_params.count( ) > 1 )
			{
				QString s_param( list_params.at( 0 ) ),
						s_value( list_params.at( 1 ) );
				qDebug( ) << "insert" << s_param << ":" << s_value;
				this->_hash_params.insert( s_param, s_value );
			}
		}
        fcfg.close( );
    }

    /// ------------------------------------------------------------------------
    /// save_cfg_file( const QString &f_path )
    /// ------------------------------------------------------------------------
    void application_params::save_cfg_file(const QString &f_path)
    {
        if( f_path.length( ) )
        {
            this->_f_path = f_path;
        }
        QFile fcfg( this->_f_path );
		fcfg.open( QIODevice::Truncate|QIODevice::WriteOnly );
        //connect file to stream
		QTextStream stream( &fcfg );
		stream.setCodec( "UTF-8" );
		qDebug( ) << "parsing ini file...\n";
        QList<QString> keys = this->_hash_params.keys( );
        for( int i = 0; i < keys.size( ); ++i )
        {
            const QString &skey = keys.at(i);
            if( skey.length( ) )
            {
                stream << skey << "#:#" << this->_hash_params[skey] << "\r\n";
            }
        }
        stream.flush( );
        fcfg.close( );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///
    /// ------------------------------------------------------------------------

}//namespace utils

}//namespace espira
