///$Header
/// ============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 16-01-2014
//		Comment		:
/// ============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_mediator.h"
#include "qt_sqlite_command.h"

namespace mac_mediator
{
	const QString data_adapter_mediator::_s_sql_newkey(
								"SELECT max(i_mediator)+1 FROM t_mediator;"
															);
	const QString data_adapter_mediator::_s_sql_insert(
								"INSERT INTO t_mediator "
								"(i_mediator, x_mediator, "
								"x_mediator_phone, x_note) "
								"   VALUES(:i_mediator, :x_mediator, "
											":x_mediator_phone, :x_note);"
									);
	const QString data_adapter_mediator::_s_sql_update(
								"UPDATE t_mediator"
								"   SET x_mediator=:x_mediator, "
										"x_mediator_phone=:x_mediator_phone, "
										"x_note=:x_note "
								"WHERE i_mediator=:i_mediator;"
									);
	const QString data_adapter_mediator::_s_sql_delete(
								"DELETE FROM t_mediator "
								"WHERE i_mediator=:i_mediator;"
									);
	const QString data_adapter_mediator::_s_sql_select(
								"SELECT i_mediator, x_mediator, "
                                        "x_mediator_phone, x_note "
								"FROM t_mediator "
									);

    const QString data_adapter_mediator::_s_sql_select_one(
                                "SELECT i_mediator, x_mediator, "
                                        "x_mediator_phone, x_note "
                                "FROM t_mediator "
                                "WHERE i_mediator=:i_mediator;"
                                    );

    const QString data_adapter_mediator::_s_sql_select_authirized(
                                "SELECT t_mediator.i_mediator, t_mediator.x_mediator, "
                                        "t_mediator.x_mediator_phone, t_mediator.x_note "
                                "FROM t_mediator, t_mediator_login "
                                "WHERE ((t_mediator_login.i_mediator=t_mediator.i_mediator)"
                                        "AND(t_mediator_login.x_login=:x_login)"
                                        "AND(t_mediator_login.x_hash=:x_hash));"
                                    );

    const QString data_adapter_mediator::_s_sql_select_permissions(
                                "SELECT x_permissions "
                                "FROM t_mediator_permissions "
                                "WHERE i_mediator=:i_mediator;"
                                                                  );

/// ############################################################################
///			class data_adapter_mediator
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
	///	~data_adapter_mediator( )
    ///------------------------------------------------------------------------
    data_adapter_mediator::~data_adapter_mediator( )
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
    ///------------------------------------------------------------------------
    void data_adapter_mediator::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

        throw std::runtime_error( sMsg.toUtf8( ).data( ) );
    }

    ///------------------------------------------------------------------------
    ///	cmd_params_select_authorized( )
    ///------------------------------------------------------------------------
    void data_adapter_mediator::cmd_params_select_authorized(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const QString &x_login,
                                            const QString &x_hash
                                                            ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( x_login ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( x_hash ) );
    }

    ///------------------------------------------------------------------------
    ///	cmd_params_select_permissions( )
    ///------------------------------------------------------------------------
    void data_adapter_mediator::cmd_params_select_permissions(
                                            espira::db::qt_sqlite_command *pcmd,
                                            int id_mediator
                                                             ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( id_mediator ) );
    }

	///------------------------------------------------------------------------
	///	check_dbms( )
    ///------------------------------------------------------------------------
    void data_adapter_mediator::check_dbms( ) const
	{
	/*
		if( !this->_dbms || !this->_dbms->is_connected( ) )
		{
			this->throw_error(
								"The program database isn't exists "
								"or it isn't connected"
							  );
		}
		*/
	}

	///------------------------------------------------------------------------
	///	execute( const QString &s_sql ) const
    ///------------------------------------------------------------------------
    void data_adapter_mediator::execute(
											const QString &s_sql,
											const data_mediator &r
										) const
	{
	/*
		this->check_dbms( );
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
		this->make_params( r, params, param_names );
		//run query
		this->_dbms->execute( s_sql, params, param_names );
		*/
	}

	///------------------------------------------------------------------------
	///	newkey( )
    ///------------------------------------------------------------------------
    int data_adapter_mediator::newkey( ) const
	{
	/*
		this->check_dbms( );

		QVariant val = this->_dbms->execute_scalar(
													this->_s_sql_newkey,
													QVector<QVariant>( )
												  );
		if( !val.isValid( ) )
		{
			this->throw_error(
								"Error in database query."
								"The value of request key isn't valid."
							  );
		}
*/
		return 0;
	}

	///------------------------------------------------------------------------
	///	select( ) const
    ///------------------------------------------------------------------------
    data_mediator_collection*
		data_adapter_mediator::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_mediator::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_mediator_collection *request_coll = 0;
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
                request_coll = new data_mediator_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    request_coll->append( new data_mediator( r ) );
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
            if( request_coll )
            {
                request_coll->free( );
                delete request_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return request_coll;
    }

    ///------------------------------------------------------------------------
    ///	select( int id_authorized_mediator ) const
    ///------------------------------------------------------------------------
    data_mediator_collection *data_adapter_mediator::select( int id_authorized_mediator ) const
    {
        //make select query
        QString s_qry( data_adapter_mediator::_s_sql_select_one );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_mediator_collection *request_coll = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //add parameter
            pcmd->parameters( ).append(
                 new espira::db::qt_sqlite_dbvalue_int( id_authorized_mediator )
                                      );
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
                request_coll = new data_mediator_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    request_coll->append( new data_mediator( r ) );
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
            if( request_coll )
            {
                request_coll->free( );
                delete request_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return request_coll;
    }

    ///------------------------------------------------------------------------
    ///	select_permissions( int id_mediator ) const
    ///------------------------------------------------------------------------
    QString data_adapter_mediator::select_permissions( int id_mediator ) const
    {
        //make select query
        QString s_qry( data_adapter_mediator::_s_sql_select_permissions );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        QVariant v_permissions(QString(""));
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //add parameters
            this->cmd_params_select_permissions( pcmd, id_mediator );
            //open cmd
            pcmd->open( );
            //exec
            v_permissions = pcmd->execute_scalar( );
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
            v_permissions.setValue( QString("") );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return v_permissions.toString( );
    }

    ///------------------------------------------------------------------------
    ///	select_authorized( ) const
    ///------------------------------------------------------------------------
    data_mediator* data_adapter_mediator::select_authorized(
                                                        const QString &x_login,
                                                        const QString &x_hash
                                                           ) const
    {
        //make select query
        QString s_qry( data_adapter_mediator::_s_sql_select_authirized );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_mediator* mediator = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //add parameters
            this->cmd_params_select_authorized( pcmd, x_login, x_hash );
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
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                mediator = new data_mediator( *iter );
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
            if( mediator )
            {
                delete mediator;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return mediator;
    }

	///------------------------------------------------------------------------
	///	insert( const data_mediator &request ) const
    ///------------------------------------------------------------------------
    void data_adapter_mediator::insert( const data_mediator &request ) const
	{
//		this->execute( data_adapter_mediator::_s_sql_insert, request );
	}

	///------------------------------------------------------------------------
	///	update( const data_mediator &request ) const
    ///------------------------------------------------------------------------
    void data_adapter_mediator::update( const data_mediator &request ) const
	{
	//	this->execute( data_adapter_mediator::_s_sql_update, request );
	}

	///------------------------------------------------------------------------
	///	del( const data_mediator &request ) const
    ///------------------------------------------------------------------------
    void data_adapter_mediator::del( const data_mediator &request ) const
	{
	/*
		this->check_dbms( );
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
		params << request.request_key( );
		param_names << "i_request";
		//run query
		this->_dbms->execute(
							data_adapter_mediator::_s_sql_delete,
							params, param_names
							);
							*/
	}

/// ############################################################################

}//namespace mac_mediator
