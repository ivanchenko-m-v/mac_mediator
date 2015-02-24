//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 25-09-2013
//		Date update	: 25-09-2013
//		Comment		:
//=============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "data_adapter_request_type.h"
#include "qt_sqlite_command.h"

namespace mac_mediator
{
	const QString data_adapter_request_type::_s_sql_newkey(
								"SELECT max(i_municipal_district)+1 "
								"FROM t_municipal_district;"
															);
	const QString data_adapter_request_type::_s_sql_insert(
								"INSERT INTO t_municipal_district "
								"(i_municipal_district, "
								" i_class_code_md,  i_administrative_division, "
								"x_municipal_district) "
								"   VALUES(:i_mr, :i_cc, :i_ad, "
											":x_md);"
									);
	const QString data_adapter_request_type::_s_sql_update(
								"UPDATE t_municipal_district"
								"   SET i_class_code_md=:i_cc, "
                                        "i_administrative_division=:i_ad, "
										"x_municipal_district=:x_md "
								"WHERE i_municipal_district=:i_mr;"
									);
	const QString data_adapter_request_type::_s_sql_delete(
								"DELETE FROM t_municipal_district "
								"WHERE i_municipal_district=:i_md;"
									);
	const QString data_adapter_request_type::_s_sql_select(
								"SELECT i_municipal_district, "
								" i_class_code_md,  i_administrative_division, "
								"x_municipal_district "
								"FROM t_municipal_district;"
									);

//#############################################################################
//			class data_adapter_request_type
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	~data_adapter_request_type( )
	///
	data_adapter_request_type::~data_adapter_request_type( )
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
	void data_adapter_request_type::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
	///	check_dbms( )
	///
	void data_adapter_request_type::check_dbms( ) const
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
	///	make_filter( const data_adapter_ad &r_filter )
	///
	QString data_adapter_request_type::make_filter(
											const data_request_type &ad
											   ) const
	{
		QString s_filter( "" );
		/*
		if( ad.zipcode( ).length( ) )
		{
			s_filter += "((x_zipcode='" + ad.zipcode( ) + "')OR";
			s_filter += "(x_zipcode LIKE '%" + ad.zipcode( ) + "')OR";
			s_filter += "(x_zipcode LIKE '%" + ad.zipcode( ) + "%')OR";
			s_filter += "(x_zipcode LIKE '" + ad.zipcode( ) + "%'))AND";
		}
		if( ad.state( ).length( ) )
		{
			s_filter += "((x_state='" + ad.state( ) + "')OR";
			s_filter += "(x_state LIKE '%" + ad.state( ) + "')OR";
			s_filter += "(x_state LIKE '%" + ad.state( ) + "%')OR";
			s_filter += "(x_state LIKE '" + ad.state( ) + "%'))AND";
		}
		if( ad.region( ).length( ) )
		{
			s_filter += "((x_region='" + ad.region( ) + "')OR";
			s_filter += "(x_region LIKE '%" + ad.region( ) + "')OR";
			s_filter += "(x_region LIKE '%" + ad.region( ) + "%')OR";
			s_filter += "(x_region LIKE '" + ad.region( ) + "%'))AND";
		}
		if( ad.city( ).length( ) )
		{
			s_filter += "((x_city='" + ad.city( ) + "')OR";
			s_filter += "(x_city LIKE '%" + ad.city( ) + "')OR";
			s_filter += "(x_city LIKE '%" + ad.city( ) + "%')OR";
			s_filter += "(x_city LIKE '" + ad.city( ) + "%'))AND";
		}
		if( ad.street( ).length( ) )
		{
			s_filter += "((x_street='" + ad.street( ) + "')OR";
			s_filter += "(x_street LIKE '%" + ad.street( ) + "')OR";
			s_filter += "(x_street LIKE '%" + ad.street( ) + "%')OR";
			s_filter += "(x_street LIKE '" + ad.street( ) + "%'))AND";
		}
		if( ad.house( ).length( ) )
		{
			s_filter += "((x_house='" + ad.house( ) + "')OR";
			s_filter += "(x_house LIKE '%" + ad.house( ) + "')OR";
			s_filter += "(x_house LIKE '%" + ad.house( ) + "%')OR";
			s_filter += "(x_house LIKE '" + ad.house( ) + "%'))AND";
		}
		if( ad.ad( ).length( ) )
		{
			s_filter += "((x_ad='" + ad.ad( ) + "')OR";
			s_filter += "(x_ad LIKE '%" + ad.ad( ) + "')OR";
			s_filter += "(x_ad LIKE '%" + ad.ad( ) + "%')OR";
			s_filter += "(x_ad LIKE '" + ad.ad( ) + "%'))AND";
		}
		if( ad.contact_name( ).length( ) )
		{
			s_filter += "((x_contact_name='" + ad.contact_name( ) + "')OR";
			s_filter += "(x_contact_name LIKE '%" + ad.contact_name( ) + "')OR";
			s_filter += "(x_contact_name LIKE '%" + ad.contact_name( ) + "%')OR";
			s_filter += "(x_contact_name LIKE '" + ad.contact_name( ) + "%'))AND";
		}
		if(
			s_filter.length() &&
			s_filter.indexOf( "AND", s_filter.length( ) - 3 ) > 0
		  )
		{
			s_filter.remove( s_filter.length( ) - 3, 3 );
		}
*/
		return s_filter;
	}

	///------------------------------------------------------------------------
	///	make_params
	///
	void data_adapter_request_type::make_params(
											const data_request_type &r,
											QVector<QVariant> &params,
											QVector<QString> &param_names
											) const
	{
	/*
		//fill params
		params	<< r.ad_key( ) << r.zipcode( ) << r.state( )
				<< r.region( ) << r.city( ) << r.street( )
				<< r.house( ) << r.ad( ) << r.contact_name( );
		//fill param's names
		param_names	<< "i_ad" << "x_zipcode" << "x_state"
					<< "x_region" << "x_city" << "x_street"
					<< "x_house" << "x_ad" << "x_contact_name";
					*/
	}

	///------------------------------------------------------------------------
	///	execute( const QString &s_sql ) const
	///
	void data_adapter_request_type::execute(
											const QString &s_sql,
											const data_request_type &r
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
	int data_adapter_request_type::newkey( ) const
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
	data_request_type_collection*
		data_adapter_request_type::select( const data_request_type &s_filter ) const
	{
		//make select query
        QString s_qry( data_adapter_request_type::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( s_filter ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_request_type_collection *mr_coll = 0;
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
                mr_coll = new data_request_type_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    mr_coll->append( new data_request_type( r ) );
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
	void data_adapter_request_type::insert( const data_request_type &ad ) const
	{
//		this->execute( data_adapter_request_type::_s_sql_insert, ad );
	}

	///------------------------------------------------------------------------
	///	update( const data_adapter_ad &ad ) const
	///
	void data_adapter_request_type::update( const data_request_type &ad ) const
	{
	//	this->execute( data_adapter_request_type::_s_sql_update, ad );
	}

	///------------------------------------------------------------------------
	///	del( const data_request_type &ad ) const
	///
	void data_adapter_request_type::del( const data_request_type &ad ) const
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
							data_adapter_request_type::_s_sql_delete,
							params, param_names
							);
							*/
	}

//#############################################################################

}//namespace mac_mediator
