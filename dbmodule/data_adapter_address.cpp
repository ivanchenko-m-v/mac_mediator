/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 25-06-2013
///		Date update	: 23-10-2013
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

#include "data_adapter_address.h"
#include "qt_sqlite_connection.h"
#include "qt_sqlite_command.h"
#include "qt_data_row.h"

namespace mac_mediator
{
    const QString data_adapter_address::_s_sql_newkey(
                                "SELECT max(i_address)+1 FROM t_address;"
															);
    const QString data_adapter_address::_s_sql_insert(
                                "INSERT INTO t_address "
                                "(i_address, x_zipcode, x_state, "
								"x_region, x_city, x_street, x_house, "
                                "x_address, x_contact_name)"
                                "   VALUES(:i_address, :x_zipcode, "
											":x_state, :x_region, :x_city, "
											":x_street, :x_house, "
                                            ":x_address, :x_contact_name);"
									);
    const QString data_adapter_address::_s_sql_update(
                                "UPDATE t_address"
								"   SET x_zipcode=:x_zipcode, "
										"x_state=:x_state, x_region=:x_region, "
										"x_city=:x_city, x_street=:x_street, "
										"x_house=:x_house, "
                                        "x_address=:x_address, "
										"x_contact_name=:x_contact_name "
                                "WHERE i_address=:i_address;"
									);
    const QString data_adapter_address::_s_sql_delete(
                                "DELETE FROM t_address "
                                "WHERE i_address=:i_address;"
									);
    const QString data_adapter_address::_s_sql_select(
                                "SELECT i_code_TIB, i_code_TIB_extra, i_code_street, "
										"i_municipal_district, x_building_address "
                                "FROM t_building_address "
									);

/// ############################################################################
///			class data_adapter_address
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_address( )
	///
    data_adapter_address::~data_adapter_address( )
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
    void data_adapter_address::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
    ///	make_filter( const data_address &r_filter )
	///
    QString data_adapter_address::make_filter(
                                            const QString &s_filter
											   ) const
	{
		QString s_res( "((instr(x_building_address,'" + s_filter + "')>0)OR" );
        s_res += "(instr(x_building_address,'" + s_filter.toUpper( ) + "')>0)OR";
        s_res += "(instr(x_building_address,'" +
                     s_filter.right(s_filter.length( ) - 1 ).
                                        prepend( s_filter[0].toUpper( ) ) +
                    "')>0))";

		return s_res;
	}

	///------------------------------------------------------------------------
	///	make_params
	///
    void data_adapter_address::make_params(
                                            const data_address &r,
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
    void data_adapter_address::execute(
											const QString &s_sql,
                                            const data_address &r
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
    int data_adapter_address::newkey( ) const
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
    ///	select( const data_address &r_filter ) const
	///
    data_address_collection*
        data_adapter_address::select( const QString &s_filter ) const
	{
        //must be entered min syms count for search
        if( s_filter.length( ) < minimum_syms_for_search )
        {
            return 0;
        }
		//make select query
        QString s_qry( data_adapter_address::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( s_filter ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_address_collection *addr_coll = 0;
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
                addr_coll = new data_address_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    addr_coll->append( new data_address( r ) );
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
	}

	///------------------------------------------------------------------------
    ///	insert( const data_address &address ) const
	///
    void data_adapter_address::insert( const data_address &address ) const
	{
        this->execute( data_adapter_address::_s_sql_insert, address );
	}

	///------------------------------------------------------------------------
    ///	update( const data_address &address ) const
	///
    void data_adapter_address::update( const data_address &address ) const
	{
        this->execute( data_adapter_address::_s_sql_update, address );
	}

	///------------------------------------------------------------------------
    ///	del( const data_address &address ) const
	///
    void data_adapter_address::del( const data_address &address ) const
	{
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
        params << address.address_key( );
        param_names << "i_address";
        /*
		//run query
		this->_dbms->execute(
                            data_adapter_address::_s_sql_delete,
							params, param_names
							);
                            */
	}

/// ############################################################################

}//namespace mac_mediator
