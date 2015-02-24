//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 25-09-2013
//		Date update	: 01-10-2013
//		Comment		:
//=============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_request_category.h"
#include "qt_sqlite_command.h"

namespace mac_mediator
{
	const QString data_adapter_request_category::_s_sql_newkey(
								"SELECT max(i_request_category)+1 "
								"FROM t_request_category;"
															);
	const QString data_adapter_request_category::_s_sql_insert(
								"INSERT INTO t_request_category "
								"(i_request_category, x_request_category) "
								"   VALUES(:i_request_category, "
											":x_request_category);"
									);
	const QString data_adapter_request_category::_s_sql_update(
								"UPDATE t_request_category"
								"   SET x_request_category=:x_request_category "
								"WHERE i_request_category=:i_request_category;"
									);
	const QString data_adapter_request_category::_s_sql_delete(
								"DELETE FROM t_request_category "
								"WHERE i_request_category=:i_request_category;"
									);
	const QString data_adapter_request_category::_s_sql_select(
								"SELECT i_request_category, x_request_category "
								"FROM t_request_category;"
									);

//#############################################################################
//			class data_adapter_request_category
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	~data_adapter_request_category( )
	///
	data_adapter_request_category::~data_adapter_request_category( )
	{
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
	///	throw_error( const char* s_msg ) const
	///
	void data_adapter_request_category::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
	///	check_dbms( )
	///
	void data_adapter_request_category::check_dbms( ) const
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
    /*

	///------------------------------------------------------------------------
	///	make_params
	///
	void data_adapter_request_category::make_params(
											const data_request_category &r,
											QVector<QVariant> &params,
											QVector<QString> &param_names
											) const
	{
		//fill params
		params	<< r.ad_key( ) << r.zipcode( ) << r.state( )
				<< r.region( ) << r.city( ) << r.street( )
				<< r.house( ) << r.ad( ) << r.contact_name( );
		//fill param's names
		param_names	<< "i_ad" << "x_zipcode" << "x_state"
					<< "x_region" << "x_city" << "x_street"
					<< "x_house" << "x_ad" << "x_contact_name";
	}
                    */

	///------------------------------------------------------------------------
	///	execute( const QString &s_sql ) const
	///
	void data_adapter_request_category::execute(
											const QString &s_sql,
											const data_request_category &r
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
	///
	int data_adapter_request_category::newkey( ) const
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
								"The value of ad key isn't valid."
							  );
		}
*/
		return 0;
	}

	///------------------------------------------------------------------------
	///	select( const data_adapter_ad &r_filter ) const
	///
	data_request_category_collection*
		data_adapter_request_category::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_request_category::_s_sql_select );
        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_request_category_collection *mr_coll = 0;
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
                mr_coll = new data_request_category_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    mr_coll->append( new data_request_category( r ) );
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
            if( mr_coll )
            {
                mr_coll->free( );
                delete mr_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return mr_coll;
	}

	///------------------------------------------------------------------------
	///	insert( const data_adapter_ad &ad ) const
	///
	void data_adapter_request_category::insert( const data_request_category &ad ) const
	{
//		this->execute( data_adapter_request_category::_s_sql_insert, ad );
	}

	///------------------------------------------------------------------------
	///	update( const data_adapter_ad &ad ) const
	///
	void data_adapter_request_category::update( const data_request_category &ad ) const
	{
	//	this->execute( data_adapter_request_category::_s_sql_update, ad );
	}

	///------------------------------------------------------------------------
	///	del( const data_request_category &ad ) const
	///
	void data_adapter_request_category::del( const data_request_category &ad ) const
	{
	/*
		this->check_dbms( );
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
		params << ad.ad_key( );
		param_names << "i_ad";
		//run query
		this->_dbms->execute(
							data_adapter_request_category::_s_sql_delete,
							params, param_names
							);
							*/
	}

//#############################################################################

}//namespace mac_mediator
