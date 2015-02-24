//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 03-11-2010
//		Date update	: 13-12-2010
//		Comment		:
//=============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "data_adapter_recipient.h"

namespace envelope_printing
{
	const QString data_adapter_recipient::_s_sql_newkey(
								"SELECT max(i_recipient)+1 FROM t_recipient;"
															);
	const QString data_adapter_recipient::_s_sql_insert(
								"INSERT INTO t_recipient "
								"(i_recipient, x_zipcode, x_state, "
								"x_region, x_city, x_street, x_house, "
								"x_recipient, x_contact_name)"
								"   VALUES(:i_recipient, :x_zipcode, "
											":x_state, :x_region, :x_city, "
											":x_street, :x_house, "
											":x_recipient, :x_contact_name);"
									);
	const QString data_adapter_recipient::_s_sql_update(
								"UPDATE t_recipient"
								"   SET x_zipcode=:x_zipcode, "
										"x_state=:x_state, x_region=:x_region, "
										"x_city=:x_city, x_street=:x_street, "
										"x_house=:x_house, "
										"x_recipient=:x_recipient, "
										"x_contact_name=:x_contact_name "
								"WHERE i_recipient=:i_recipient;"
									);
	const QString data_adapter_recipient::_s_sql_delete(
								"DELETE FROM t_recipient "
								"WHERE i_recipient=:i_recipient;"
									);
	const QString data_adapter_recipient::_s_sql_select(
								"SELECT i_recipient, x_zipcode, x_state, "
										"x_region, x_city, x_street, x_house, "
										"x_recipient, x_contact_name "
								"FROM t_recipient "
									);
	const QString data_adapter_recipient::_s_sql_states(
								"SELECT DISTINCT x_state "
								"FROM t_recipient;"
									);
	const QString data_adapter_recipient::_s_sql_regions(
								"SELECT DISTINCT x_region "
								"FROM t_recipient;"
									);

//#############################################################################
//			class data_adapter_recipient
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	~data_adapter_recipient( )
	///
	data_adapter_recipient::~data_adapter_recipient( )
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
	void data_adapter_recipient::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	///------------------------------------------------------------------------
	///	check_dbms( )
	///
	void data_adapter_recipient::check_dbms( ) const
	{
		if( !this->_dbms || !this->_dbms->is_connected( ) )
		{
			this->throw_error(
								"The program database isn't exists "
								"or it isn't connected"
							  );
		}
	}

	///------------------------------------------------------------------------
	///	make_filter( const data_recipient &r_filter )
	///
	QString data_adapter_recipient::make_filter(
											const data_recipient &recipient
											   ) const
	{
		QString s_filter( "" );
		if( recipient.zipcode( ).length( ) )
		{
			s_filter += "((x_zipcode='" + recipient.zipcode( ) + "')OR";
			s_filter += "(x_zipcode LIKE '%" + recipient.zipcode( ) + "')OR";
			s_filter += "(x_zipcode LIKE '%" + recipient.zipcode( ) + "%')OR";
			s_filter += "(x_zipcode LIKE '" + recipient.zipcode( ) + "%'))AND";
		}
		if( recipient.state( ).length( ) )
		{
			s_filter += "((x_state='" + recipient.state( ) + "')OR";
			s_filter += "(x_state LIKE '%" + recipient.state( ) + "')OR";
			s_filter += "(x_state LIKE '%" + recipient.state( ) + "%')OR";
			s_filter += "(x_state LIKE '" + recipient.state( ) + "%'))AND";
		}
		if( recipient.region( ).length( ) )
		{
			s_filter += "((x_region='" + recipient.region( ) + "')OR";
			s_filter += "(x_region LIKE '%" + recipient.region( ) + "')OR";
			s_filter += "(x_region LIKE '%" + recipient.region( ) + "%')OR";
			s_filter += "(x_region LIKE '" + recipient.region( ) + "%'))AND";
		}
		if( recipient.city( ).length( ) )
		{
			s_filter += "((x_city='" + recipient.city( ) + "')OR";
			s_filter += "(x_city LIKE '%" + recipient.city( ) + "')OR";
			s_filter += "(x_city LIKE '%" + recipient.city( ) + "%')OR";
			s_filter += "(x_city LIKE '" + recipient.city( ) + "%'))AND";
		}
		if( recipient.street( ).length( ) )
		{
			s_filter += "((x_street='" + recipient.street( ) + "')OR";
			s_filter += "(x_street LIKE '%" + recipient.street( ) + "')OR";
			s_filter += "(x_street LIKE '%" + recipient.street( ) + "%')OR";
			s_filter += "(x_street LIKE '" + recipient.street( ) + "%'))AND";
		}
		if( recipient.house( ).length( ) )
		{
			s_filter += "((x_house='" + recipient.house( ) + "')OR";
			s_filter += "(x_house LIKE '%" + recipient.house( ) + "')OR";
			s_filter += "(x_house LIKE '%" + recipient.house( ) + "%')OR";
			s_filter += "(x_house LIKE '" + recipient.house( ) + "%'))AND";
		}
		if( recipient.recipient( ).length( ) )
		{
			s_filter += "((x_recipient='" + recipient.recipient( ) + "')OR";
			s_filter += "(x_recipient LIKE '%" + recipient.recipient( ) + "')OR";
			s_filter += "(x_recipient LIKE '%" + recipient.recipient( ) + "%')OR";
			s_filter += "(x_recipient LIKE '" + recipient.recipient( ) + "%'))AND";
		}
		if( recipient.contact_name( ).length( ) )
		{
			s_filter += "((x_contact_name='" + recipient.contact_name( ) + "')OR";
			s_filter += "(x_contact_name LIKE '%" + recipient.contact_name( ) + "')OR";
			s_filter += "(x_contact_name LIKE '%" + recipient.contact_name( ) + "%')OR";
			s_filter += "(x_contact_name LIKE '" + recipient.contact_name( ) + "%'))AND";
		}
		if(
			s_filter.length() &&
			s_filter.indexOf( "AND", s_filter.length( ) - 3 ) > 0
		  )
		{
			s_filter.remove( s_filter.length( ) - 3, 3 );
		}

		return s_filter;
	}

	///------------------------------------------------------------------------
	///	make_params
	///
	void data_adapter_recipient::make_params(
											const data_recipient &r,
											QVector<QVariant> &params,
											QVector<QString> &param_names
											) const
	{
		//fill params
		params	<< r.recipient_key( ) << r.zipcode( ) << r.state( )
				<< r.region( ) << r.city( ) << r.street( )
				<< r.house( ) << r.recipient( ) << r.contact_name( );
		//fill param's names
		param_names	<< "i_recipient" << "x_zipcode" << "x_state"
					<< "x_region" << "x_city" << "x_street"
					<< "x_house" << "x_recipient" << "x_contact_name";
	}

	///------------------------------------------------------------------------
	///	execute( const QString &s_sql ) const
	///
	void data_adapter_recipient::execute(
											const QString &s_sql,
											const data_recipient &r
										) const
	{
		this->check_dbms( );
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
		this->make_params( r, params, param_names );
		//run query
		this->_dbms->execute( s_sql, params, param_names );
	}

	///------------------------------------------------------------------------
	///	newkey( )
	///
	int data_adapter_recipient::newkey( ) const
	{
		this->check_dbms( );

		QVariant val = this->_dbms->execute_scalar(
													this->_s_sql_newkey,
													QVector<QVariant>( )
												  );
		if( !val.isValid( ) )
		{
			this->throw_error(
								"Error in database query."
								"The value of recipient key isn't valid."
							  );
		}

		return val.toInt( );
	}

	///------------------------------------------------------------------------
	///	select( const data_recipient &r_filter ) const
	///
	data_recipient_collection*
		data_adapter_recipient::select( const data_recipient &r_filter ) const
	{
		this->check_dbms( );
		//make select query
		QString s_filter( this->make_filter( r_filter ) );
		QString s_qry =	data_adapter_recipient::_s_sql_select +
						( s_filter.length( ) ? "WHERE " + s_filter : "" );
		s_qry += ";";
		//run query
		espira::qt_data_row_collection *p_rows =
							this->_dbms->select( s_qry, QVector<QVariant>( ) );

		data_recipient_collection *recipients = new data_recipient_collection;
		for( int i = 0; i < p_rows->size( ); ++i )
		{
			//make data_recipient from current row
			data_recipient *r = new data_recipient( (*p_rows)[i] );
			//append data_recipient to list
			recipients->append( r );
		}
		//free query result qt_data_row_collection
		delete p_rows;

		return recipients;
	}

	///------------------------------------------------------------------------
	///	insert( const data_recipient &recipient ) const
	///
	void data_adapter_recipient::insert( const data_recipient &recipient ) const
	{
		this->execute( data_adapter_recipient::_s_sql_insert, recipient );
	}

	///------------------------------------------------------------------------
	///	update( const data_recipient &recipient ) const
	///
	void data_adapter_recipient::update( const data_recipient &recipient ) const
	{
		this->execute( data_adapter_recipient::_s_sql_update, recipient );
	}

	///------------------------------------------------------------------------
	///	del( const data_recipient &recipient ) const
	///
	void data_adapter_recipient::del( const data_recipient &recipient ) const
	{
		this->check_dbms( );
		//prepare parameters
		QVector<QVariant> params;
		QVector<QString> param_names;
		params << recipient.recipient_key( );
		param_names << "i_recipient";
		//run query
		this->_dbms->execute(
							data_adapter_recipient::_s_sql_delete,
							params, param_names
							);
	}

	///------------------------------------------------------------------------
	///	string_list( ) const
	///
	void data_adapter_recipient::string_list(
												const QString &s_qry,
												QStringList &lst
											) const
	{
		this->check_dbms( );

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

	///------------------------------------------------------------------------
	///	states( ) const
	///
	void data_adapter_recipient::states( QStringList &l_states ) const
	{
		this->string_list( data_adapter_recipient::_s_sql_states, l_states );
	}

	///------------------------------------------------------------------------
	///	regions( ) const
	///
	void data_adapter_recipient::regions( QStringList &l_regions ) const
	{
		this->string_list( data_adapter_recipient::_s_sql_regions, l_regions );
	}

//#############################################################################

}//namespace envelope_printing
