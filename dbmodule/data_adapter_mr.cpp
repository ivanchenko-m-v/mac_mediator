//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 22-09-2013
//		Date update	: 22-09-2013
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

#include "data_adapter_mr.h"
#include "qt_sqlite_command.h"

namespace mac_mediator
{
	const QString data_adapter_mr::_s_sql_newkey(
								"SELECT max(i_municipal_district)+1 "
								"FROM t_municipal_district;"
															);
	const QString data_adapter_mr::_s_sql_insert(
								"INSERT INTO t_municipal_district "
								"(i_municipal_district, "
								" i_class_code_md,  i_administrative_division, "
								"x_municipal_district) "
								"   VALUES(:i_mr, :i_cc, :i_ad, "
											":x_md);"
									);
	const QString data_adapter_mr::_s_sql_update(
								"UPDATE t_municipal_district"
								"   SET i_class_code_md=:i_cc, "
                                        "i_administrative_division=:i_ad, "
										"x_municipal_district=:x_md "
								"WHERE i_municipal_district=:i_mr;"
									);
	const QString data_adapter_mr::_s_sql_delete(
								"DELETE FROM t_municipal_district "
								"WHERE i_municipal_district=:i_md;"
									);
	const QString data_adapter_mr::_s_sql_select(
								"SELECT i_municipal_district, "
								" i_class_code_md,  i_administrative_division, "
								"x_municipal_district "
								"FROM t_municipal_district "
									);

//#############################################################################
//			class data_adapter_mr
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	~data_adapter_mr( )
	///
	data_adapter_mr::~data_adapter_mr( )
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
	void data_adapter_mr::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
	///	check_dbms( )
	///
	void data_adapter_mr::check_dbms( ) const
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
	QString data_adapter_mr::make_filter( const data_mr &mr ) const
	{
		QString s_filter( "" );
        if( mr.ad_id( ) > 0 )
		{
			s_filter += "(i_administrative_division=" +
                        QString::number( mr.ad_id( ) ) +")";
		}
		if( mr.class_code_id( ) > 0 )
		{
            if( s_filter.length( ) )
            {
                s_filter+="OR";
            }
			s_filter += "(i_class_code_md=" +
                        QString::number( mr.class_code_id( ) ) + ")";
		}
		if( mr.mr_title( ).length( ) )
		{
            if( s_filter.length( ) )
            {
                s_filter+="OR";
            }
			s_filter += "((x_municipal_district='" + mr.mr_title( ) + "')OR";
			s_filter += "(x_municipal_district LIKE '%" + mr.mr_title( ) + "')OR";
			s_filter += "(x_municipal_district LIKE '%" + mr.mr_title( ) + "%')OR";
			s_filter += "(x_municipal_district LIKE '" + mr.mr_title( ) + "%'))";
		}

        if(s_filter.length() )
        {
            s_filter.prepend('(');
            s_filter.append(')');
        }

        return s_filter;
	}

	///------------------------------------------------------------------------
	///	make_params
	///
	void data_adapter_mr::make_params(
											const data_mr &r,
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
	void data_adapter_mr::execute(
											const QString &s_sql,
											const data_mr &r
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
	int data_adapter_mr::newkey( ) const
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
	data_mr_collection*
		data_adapter_mr::select( const data_mr &mr ) const
	{
		//make select query
        QString s_qry( data_adapter_mr::_s_sql_select );
        s_qry += "WHERE " + this->make_filter( mr ) + ";";

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_mr_collection *mr_coll = 0;
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
                mr_coll = new data_mr_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    mr_coll->append( new data_mr( r ) );
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
	void data_adapter_mr::insert( const data_mr &ad ) const
	{
//		this->execute( data_adapter_mr::_s_sql_insert, ad );
	}

	///------------------------------------------------------------------------
	///	update( const data_adapter_ad &ad ) const
	///
	void data_adapter_mr::update( const data_mr &ad ) const
	{
	//	this->execute( data_adapter_mr::_s_sql_update, ad );
	}

	///------------------------------------------------------------------------
	///	del( const data_mr &ad ) const
	///
	void data_adapter_mr::del( const data_mr &ad ) const
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
							data_mrapter_mr::_s_sql_delete,
							params, param_names
							);
							*/
	}

//#############################################################################

}//namespace mac_mediator
