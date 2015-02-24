/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 22-09-2013
///		Date update	: 02-02-2014
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

#include "data_adapter_request.h"
#include "qt_sqlite_command.h"
#include "qt_data_parameter.h"
#include "qt_sqlite_dbvalue.h"

namespace mac_mediator
{
	const QString data_adapter_request::_s_sql_newkey(
								"SELECT max(i_request) FROM t_request "
                                    "WHERE ((i_request > :id_from)AND"
                                            "(i_request < :id_to));"
													 );
	const QString data_adapter_request::_s_sql_insert(
								"INSERT INTO t_request "
                                "(i_request, i_declarant_type, i_mr, i_mediator, "
								"i_request_category, dt_request, tm_request, "
                                "x_declarant, x_declarant_phone, x_declarant_address,"
                                "x_service_organization, x_request, x_other_conflict_party,"
                                "x_organization, x_consultation )"
                                "   VALUES(:i_request, :i_declarant_type, :i_mr, :i_mediator, "
											":i_request_category, :dt_request, :tm_request, "
											":x_declarant, :x_declarant_phone, :x_declarant_address, "
                                            ":x_service_organization, :x_request, :x_other_conflict_party,"
                                            ":x_organization, :x_consultation);"
									);
	const QString data_adapter_request::_s_sql_update(
								"UPDATE t_request"
                                "   SET i_declarant_type=:i_declarant_type, "
                                    "i_mr=:i_mr, "
                                    "i_mediator=:i_mediator, "
                                    "i_request_category=:i_request_category, "
                                    "dt_request=:dt_request, "
                                    "tm_request=:tm_request, "
                                    "x_declarant=:x_declarant, "
                                    "x_declarant_phone=:x_declarant_phone, "
                                    "x_declarant_address=:x_declarant_address, "
                                    "x_service_organization=:x_service_organization, "
                                    "x_request=:x_request, "
                                    "x_other_conflict_party=:x_other_conflict_party, "
                                    "x_organization=:x_organization, "
                                    "x_consultation=:x_consultation "
								"WHERE i_request=:i_request;"
									);
	const QString data_adapter_request::_s_sql_update_id(
								"UPDATE t_request"
								"   SET i_request=:i_new "
								"WHERE i_request=:i_old;"
									);
	const QString data_adapter_request::_s_sql_delete(
								"DELETE FROM t_request "
								"WHERE i_request=:i_request;"
									);
	const QString data_adapter_request::_s_sql_select(
            "SELECT i_request, i_declarant_type, i_mr, i_mediator, i_request_category, "
                   "dt_request, tm_request, x_declarant, x_declarant_phone, "
                   "x_declarant_address, x_service_organization, x_request, "
                   "x_other_conflict_party, x_organization, x_consultation, "
                    "i_administrative_division, "
                   "x_administrative_division, x_municipal_district, "
                   "x_mediator, x_mediator_phone, x_request_category, x_declarant_type "
                   "FROM vw_request "
                                                    );

/// ############################################################################
///			class data_adapter_request
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	~data_adapter_request( )
	///
	data_adapter_request::~data_adapter_request( )
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
	/// ------------------------------------------------------------------------
	///	throw_error( const char* s_msg ) const
    /// ------------------------------------------------------------------------
	void data_adapter_request::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    /// ------------------------------------------------------------------------
	///	make_filter( const data_request_search_criteria &r_filter )
    /// ------------------------------------------------------------------------
	QString data_adapter_request::make_filter(
									const data_request_search_criteria &criteria
											 ) const
	{
		QString s_filter( "" );

        if( criteria.id_declarant_type( ) > 0 )
        {
            s_filter += "(i_declarant_type=" +
                        QString::number( criteria.id_declarant_type( ) ) +")";
        }
        if( criteria.id_ad( ) > 0 )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
            s_filter += "(i_administrative_division=" +
                        QString::number( criteria.id_ad( ) ) +")";
		}
        if( criteria.id_mr( ) > 0 )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
			s_filter += "(i_mr=" +
                        QString::number( criteria.id_mr( ) ) +")";
		}
        if( criteria.id_mediator( ) > 0 )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
			s_filter += "(i_mediator=" +
                        QString::number( criteria.id_mediator( ) ) +")";
		}
		if( criteria.id_request_category( ) > 0 )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
			s_filter += "(i_request_category=" +
                        QString::number( criteria.id_request_category( ) ) +")";
		}
		if( criteria.date_from_string( ).length( ) )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
			s_filter += "(dt_request>=\'" + criteria.date_from_string( ) +"\')";
		}
		if( criteria.date_to_string( ).length( ) )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
			s_filter += "(dt_request<=\'" + criteria.date_to_string( ) +"\')";
		}
        QString x_declarant( criteria.declarant( ) );
        if( x_declarant.length( ) )
		{
            if( s_filter.length( ) )
            {
                s_filter += "AND";
            }
            s_filter += "((instr(x_declarant,'" + x_declarant + "')>0)OR";
            s_filter += "(instr(x_declarant,'" + x_declarant.toUpper( ) + "')>0)OR";
            s_filter += "(instr(x_declarant,'" +
                         x_declarant.right( x_declarant.length( ) - 1 ).
                                            prepend( x_declarant[0].toUpper( ) ) +
                        "')>0))";
        }

        if(s_filter.length() )
        {
            s_filter.prepend('(');
            s_filter.append(')');
        }

		return s_filter;
	}

	/// ------------------------------------------------------------------------
	///	cmd_params_insert
    /// ------------------------------------------------------------------------
	void data_adapter_request::cmd_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_request &r
                                             ) const
	{
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_declarant_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_mr( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_mediator( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_request_category( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.time_request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant_phone( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant_address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.service_organization( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.other_conflict_party( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.organization( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.consultation( ) ) );
	}

    /// ------------------------------------------------------------------------
	///	cmd_params_update
    /// ------------------------------------------------------------------------
	void data_adapter_request::cmd_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_request &r
                                             ) const
	{
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_declarant_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_mr( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_mediator( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_request_category( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.time_request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant_phone( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.declarant_address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.service_organization( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.request( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.other_conflict_party( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.organization( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.consultation( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_request( ) ) );
	}

	/// ------------------------------------------------------------------------
	///	select_id_new( int id_ad )
    /// ------------------------------------------------------------------------
    QVariant data_adapter_request::select_id_new(  int id_from, int id_to ) const
    {
        QString s_qry( data_adapter_request::_s_sql_newkey );

        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        QVariant val_id_new;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            pcmd->parameters( ).append( new espira::db::qt_sqlite_dbvalue_int( id_from ) );
            pcmd->parameters( ).append( new espira::db::qt_sqlite_dbvalue_int( id_to ) );
            //open cmd
            pcmd->open( );
            //exec
            val_id_new = pcmd->execute_scalar( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            val_id_new = QVariant( );

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
        return val_id_new;
    }

    int data_adapter_request::newkey( int i_ad, const QDate &dt ) const
	{
        int nyear = dt.year( ) - 2000;
        QVariant val = this->select_id_new( (i_ad<<24)+(nyear<<16), (i_ad<<24)+((nyear+1)<<16) );
        if( val.isNull( ) || !val.isValid( ) )
        {
            return (i_ad<<24)+(nyear<<16) + 1;
        }

		return val.toInt( ) + 1;
	}

	/// ------------------------------------------------------------------------
	///	select( const data_request_search_criteria &criteria ) const
	/// ------------------------------------------------------------------------
	data_request_collection*
		data_adapter_request::select( const data_request_search_criteria &criteria ) const
	{
		//make select query
        QString s_qry( data_adapter_request::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( criteria ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_request_collection *request_coll = 0;
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
                request_coll = new data_request_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    request_coll->append( new data_request( r ) );
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

	/// ------------------------------------------------------------------------
	///	select( const data_request &r_filter ) const
	/// ------------------------------------------------------------------------
	data_request_collection*
		data_adapter_request::select( const data_request &s_filter ) const
	{
		//make select query
        QString s_qry( data_adapter_request::_s_sql_select );
        //s_qry += "WHERE " + this->make_filter( s_filter ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_request_collection *request_coll = 0;
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
                request_coll = new data_request_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    request_coll->append( new data_request( r ) );
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

	/// ------------------------------------------------------------------------
	///	insert( const data_request &request ) const
	/// ------------------------------------------------------------------------
	void data_adapter_request::insert( const data_request &request ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_request::_s_sql_insert );
            //add parameters
            this->cmd_params_insert( pcmd, request );
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

	/// ------------------------------------------------------------------------
	///	update( const data_request &request ) const
	/// ------------------------------------------------------------------------
	void data_adapter_request::update( const data_request &request ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_request::_s_sql_update );
            //add parameters
            this->cmd_params_update( pcmd, request );
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

	/// ------------------------------------------------------------------------
	///	update_id(int id_old, int id_new) const
    /// ------------------------------------------------------------------------
    void data_adapter_request::update_id(int id_old, int id_new) const
    {
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_request::_s_sql_update_id );
            pcmd->parameters( ).append(
                        new espira::db::qt_sqlite_dbvalue_int( id_new )
                                      );
            pcmd->parameters( ).append(
                        new espira::db::qt_sqlite_dbvalue_int( id_old )
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

	/// ------------------------------------------------------------------------
	///	del( const int id_request ) const
    /// ------------------------------------------------------------------------
	void data_adapter_request::del( const int id_request ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_request::_s_sql_delete );
            pcmd->parameters( ).append(
                        new espira::db::qt_sqlite_dbvalue_int( id_request )
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
