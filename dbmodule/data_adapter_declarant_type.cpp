///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 30-01-2014
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_declarant_type.h"
#include "qt_sqlite_command.h"

namespace mac_mediator
{
    const QString data_adapter_declarant_type::_s_sql_newkey(
                                "SELECT max(i_declarant_type)+1 "
                                "FROM t_declarant_type;"
															);
    const QString data_adapter_declarant_type::_s_sql_insert(
                                "INSERT INTO t_declarant_type "
                                "(i_declarant_type, x_declarant_type) "
                                "   VALUES(:i_id, :x_title);"
									);
    const QString data_adapter_declarant_type::_s_sql_update(
                                "UPDATE t_declarant_type"
                                "   SET x_declarant_type=:x_title "
                                "WHERE i_declarant_type=:i_declarant_type;"
									);
    const QString data_adapter_declarant_type::_s_sql_delete(
                                "DELETE FROM t_declarant_type "
                                "WHERE i_declarant_type=:i_declarant_type;"
									);
    const QString data_adapter_declarant_type::_s_sql_select(
                                "SELECT i_declarant_type, x_declarant_type "
                                "FROM t_declarant_type "
									);
/// ############################################################################
///			class data_adapter_declarant_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_declarant_type( )
	///
    data_adapter_declarant_type::~data_adapter_declarant_type( )
	{
	}

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	///------------------------------------------------------------------------
	///	throw_error( const char* s_msg ) const
	///
    void data_adapter_declarant_type::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
	///	newkey( )
	///
    int data_adapter_declarant_type::newkey( ) const
	{
        //make query
        QString s_qry( data_adapter_declarant_type::_s_sql_newkey );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        QVariant retval( QVariant::Invalid );
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //open cmd
            pcmd->open( );
            //exec
            retval = pcmd->execute_scalar( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            retval = QVariant( QVariant::Invalid );
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
        return retval.isValid() ? retval.toInt( ) : -1;
	}

	///------------------------------------------------------------------------
	///	select( ) const
	///
    data_declarant_type_collection*
        data_adapter_declarant_type::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_declarant_type::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_declarant_type_collection *decl_type_coll = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );

            //output result
            espira::db::qt_data_row_collection &rows = pcmd->result( );
            if( rows.size( ) )
            {
                decl_type_coll = new data_declarant_type_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    decl_type_coll->append( new data_declarant_type( r ) );
                }
            }

            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            if( decl_type_coll )
            {
                decl_type_coll->free( );
                delete decl_type_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return decl_type_coll;
	}

    ///------------------------------------------------------------------------
    ///	bind_parameters_insert
    ///------------------------------------------------------------------------
    void data_adapter_declarant_type::bind_parameters_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            int id_new,
                                            const data_declarant_type &dt
                                                            ) const
    {
        pcmd->parameters( ).append(
            new espira::db::qt_sqlite_dbvalue_int( id_new )
                                  );
        pcmd->parameters( ).append(
            new espira::db::qt_sqlite_dbvalue_text( dt.declarant_type_title( ) )
                                  );
    }

    ///------------------------------------------------------------------------
    ///	insert( const data_declarant_type &ad ) const
	///
    void data_adapter_declarant_type::insert( data_declarant_type &dt ) const
	{
        int id_new = this->newkey( );
        if( id_new <= 0 )
        {
            id_new = 1;
        }
        //make query
        QString s_qry( data_adapter_declarant_type::_s_sql_insert );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //bind parameters
            this->bind_parameters_insert( pcmd, id_new, dt );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
        //set id declarant type if success
        dt.id_declarant_type( id_new );
    }

    ///------------------------------------------------------------------------
    ///	bind_parameters_update
    ///------------------------------------------------------------------------
    void data_adapter_declarant_type::bind_parameters_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_declarant_type &dt
                                                            ) const
    {
        pcmd->parameters( ).append(
            new espira::db::qt_sqlite_dbvalue_text( dt.declarant_type_title( ) )
                                  );
        pcmd->parameters( ).append(
            new espira::db::qt_sqlite_dbvalue_int( dt.id_declarant_type( ) )
                                  );
    }

    ///------------------------------------------------------------------------
    ///	update( const data_declarant_type &ad ) const
    ///------------------------------------------------------------------------
    void data_adapter_declarant_type::update( const data_declarant_type &dt ) const
	{
        //make query
        QString s_qry( data_adapter_declarant_type::_s_sql_update );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //bind parameters
            this->bind_parameters_update( pcmd, dt );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

	///------------------------------------------------------------------------
    ///	del( const data_declarant_type &ad ) const
	///
    void data_adapter_declarant_type::del( const data_declarant_type &dt ) const
	{
        //make query
        QString s_qry( data_adapter_declarant_type::_s_sql_delete );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //bind parameters
            pcmd->parameters( ).append(
                new espira::db::qt_sqlite_dbvalue_int( dt.id_declarant_type( ) )
                                      );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

/// ############################################################################

}//namespace mac_mediator
