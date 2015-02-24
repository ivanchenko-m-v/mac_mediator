///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 27-06-2013
///		Date update	: 25-10-2013
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

#include "data_adapter_so.h"
#include "qt_sqlite_connection.h"
#include "qt_sqlite_command.h"
#include "qt_data_row.h"

namespace mac_mediator
{
    const QString data_adapter_so::_s_sql_newkey(
                                "SELECT max(i_address)+1 FROM t_address;"
															);
    const QString data_adapter_so::_s_sql_insert(
                                "INSERT INTO t_address "
                                "(i_address, x_zipcode, x_state, "
								"x_region, x_city, x_street, x_house, "
                                "x_address, x_contact_name)"
                                "   VALUES(:i_address, :x_zipcode, "
											":x_state, :x_region, :x_city, "
											":x_street, :x_house, "
                                            ":x_address, :x_contact_name);"
									);
    const QString data_adapter_so::_s_sql_update(
                                "UPDATE t_address"
								"   SET x_zipcode=:x_zipcode, "
										"x_state=:x_state, x_region=:x_region, "
										"x_city=:x_city, x_street=:x_street, "
										"x_house=:x_house, "
                                        "x_address=:x_address, "
										"x_contact_name=:x_contact_name "
                                "WHERE i_address=:i_address;"
									);
    const QString data_adapter_so::_s_sql_delete(
                                "DELETE FROM t_address "
                                "WHERE i_address=:i_address;"
									);
    const QString data_adapter_so::_s_sql_select(
                                "SELECT i_so, x_so_title, x_so_address, "
										"x_so_phones "
                                "FROM t_service_organization "
									);

/// ############################################################################
///			class data_adapter_so
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_so( )
	///
    data_adapter_so::~data_adapter_so( )
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
    void data_adapter_so::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
    ///	make_filter( const data_so &r_filter )
	///
    QString data_adapter_so::make_filter( const long long &i_TIB_code ) const
	{
		QString s_res( "" );
        s_res += "i_so IN(SELECT i_so FROM t_building_so WHERE i_code_TIB=" +
                QString::number( i_TIB_code ) + ")";

		return s_res;
	}

	///------------------------------------------------------------------------
	///	make_params
	///
    void data_adapter_so::make_params(
                                            const data_so &r,
											QVector<QVariant> &params,
											QVector<QString> &param_names
											) const
	{
        /*
		//fill params
        params	<< r.address_key( ) << r.zipcode( ) << r.state( )
				<< r.region( ) << r.city( ) << r.street( )
                << r.house( ) << r.address( ) << r.contact_name( );
		//fill param's names
        param_names	<< "i_address" << "x_zipcode" << "x_state"
					<< "x_region" << "x_city" << "x_street"
                    << "x_house" << "x_address" << "x_contact_name";
                    */
	}

	///------------------------------------------------------------------------
	///	execute( const QString &s_sql ) const
	///
    void data_adapter_so::execute(
											const QString &s_sql,
                                            const data_so &r
										) const
	{
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
        /*
		this->make_params( r, params, param_names );
		//run query
		this->_dbms->execute( s_sql, params, param_names );
        */
	}

	///------------------------------------------------------------------------
	///	newkey( )
	///
    int data_adapter_so::newkey( ) const
	{
/*
		QVariant val = this->_dbms->execute_scalar(
													this->_s_sql_newkey,
													QVector<QVariant>( )
												  );
		if( !val.isValid( ) )
		{
			this->throw_error(
								"Error in database query."
                                "The value of address key isn't valid."
							  );
		}

        //return val.toInt( );
                                                  */
        return 0;
    }

	///------------------------------------------------------------------------
    ///	select( const data_so &r_filter ) const
	///
    data_so_collection*
        data_adapter_so::select( const QString &s_filter ) const
	{
        /*
        //must be entered min syms count for search
        if( s_filter.length( ) < minimum_syms_for_search )
        {
            return 0;
        }
		//make select query
        QString s_qry( data_adapter_so::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( s_filter ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_so_collection *addr_coll = 0;
        try
        {
            cnn.db_path("./db/db_address.sqlite3");
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
                addr_coll = new data_so_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    addr_coll->append( new data_so( r ) );
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
            if( addr_coll )
            {
                addr_coll->free( );
                delete addr_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return addr_coll;
        */
        return 0;
	}

    ///------------------------------------------------------------------------
    ///	select( const long long &i_TIB_code ) const
	///
    data_so* data_adapter_so::select( const long long &i_TIB_code ) const
	{
        //must be entered min syms count for search
        if( i_TIB_code == 0 )
        {
            return 0;
        }
		//make select query
        QString s_qry( data_adapter_so::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( i_TIB_code ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_so *so = 0;
        try
        {
            cnn.db_path( application::the_business_logic( ).db_path( ) );
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
                so = new data_so( *(rows.begin( )) );
            }

            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                delete pcmd;
                pcmd = 0;
            }
            if( so )
            {
                delete so;
                so = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return so;
	}

	///------------------------------------------------------------------------
    ///	insert( const data_so &address ) const
	///
    void data_adapter_so::insert( const data_so &address ) const
	{
        this->execute( data_adapter_so::_s_sql_insert, address );
	}

	///------------------------------------------------------------------------
    ///	update( const data_so &address ) const
	///
    void data_adapter_so::update( const data_so &address ) const
	{
        this->execute( data_adapter_so::_s_sql_update, address );
	}

	///------------------------------------------------------------------------
    ///	del( const data_so &address ) const
	///
    void data_adapter_so::del( const data_so &address ) const
	{
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
        params << address.so_key( );
        param_names << "i_so";
        /*
		//run query
		this->_dbms->execute(
                            data_adapter_so::_s_sql_delete,
							params, param_names
							);
                            */
	}

	///------------------------------------------------------------------------
	///	string_list( ) const
	///
    void data_adapter_so::string_list(
												const QString &s_qry,
												QStringList &lst
											) const
	{
/*
		espira::qt_data_row_collection *p_rows =
							this->_dbms->select( s_qry, QVector<QVariant>( ) );
		//convert rows to strings
		espira::qt_data_row_collection::iterator it = p_rows->begin( );
		for( ; it != p_rows->end( ); ++it )
		{
			espira::qt_data_row *row = *it;
			if( row->columns( ) )
			{
				lst.append( (*row)[0].toString( ) );
			}
		}
		delete p_rows;
        */
		/*
		QVector<QVector<QVariant> > result;
		//run query
		this->_dbms->select( s_qry, result, QVector<QVariant>( ) );
		//fill strings list
		QVector<QVector<QVariant> >::iterator it = result.begin( );
		for( ; it!=result.end( ); ++it )
		{
			QVector<QVariant> row = *it;
			if( row.size( ) )
			{
				lst.append( row[0].toString( ) );
			}
		}
		*/
	}

/// ############################################################################

}//namespace mac_mediator
