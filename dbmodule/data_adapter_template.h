//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 03-11-2010
//		Date update	: 17-11-2010
//		Comment		:
//=============================================================================
#ifndef __DATA_ADAPTER_RECIPIENT_H__
#define __DATA_ADAPTER_RECIPIENT_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_dbms.h"
#include "qt_data_row.h"

namespace envelope_printing
{

//#############################################################################
//			class data_recipient
//#############################################################################
	class data_recipient
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		data_recipient( ) :
			_i_recipient( 0 ),
			_x_zipcode( "" ),
			_x_state( "" ),
			_x_region( "" ),
			_x_city( "" ),
			_x_street( "" ),
			_x_house( "" ),
			_x_recipient( "" ),
			_x_contact_name( "" )
		{ }

	//-------------------------------------------------------------------------
		explicit
		data_recipient( const data_recipient &rhs ) :
			_i_recipient( rhs._i_recipient ),
			_x_zipcode( rhs._x_zipcode ),
			_x_state( rhs._x_state ),
			_x_region( rhs._x_region ),
			_x_city( rhs._x_city ),
			_x_street( rhs._x_street ),
			_x_house( rhs._x_house ),
			_x_recipient( rhs._x_recipient ),
			_x_contact_name( rhs._x_contact_name )
		{ }

	//-------------------------------------------------------------------------
		explicit
		data_recipient( const QVector<QVariant> &row ) :
			_i_recipient( row[0].toInt( ) ),
			_x_zipcode( row[1].toString( ) ),
			_x_state( row[2].toString( ) ),
			_x_region( row[3].toString( ) ),
			_x_city( row[4].toString( ) ),
			_x_street( row[5].toString( ) ),
			_x_house( row[6].toString( ) ),
			_x_recipient( row[7].toString( ) ),
			_x_contact_name( row[8].toString( ) )
		{ }

	//-------------------------------------------------------------------------
		explicit
		data_recipient( espira::qt_data_row *p_row ) :
			_i_recipient( (*p_row)[0].toInt( ) ),
			_x_zipcode( (*p_row)[1].toString( ) ),
			_x_state( (*p_row)[2].toString( ) ),
			_x_region( (*p_row)[3].toString( ) ),
			_x_city( (*p_row)[4].toString( ) ),
			_x_street( (*p_row)[5].toString( ) ),
			_x_house( (*p_row)[6].toString( ) ),
			_x_recipient( (*p_row)[7].toString( ) ),
			_x_contact_name( (*p_row)[8].toString( ) )
		{ }

	//-------------------------------------------------------------------------
		~data_recipient( )
		{
			qDebug( ) << "deleted : " << this->_x_zipcode + " " +
										 this->_x_state + " " +
										 this->_x_region + " " +
										 this->_x_city;
		}

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		void clear_data( )
		{
			this->_i_recipient = 0;
			this->_x_zipcode = "";
			this->_x_state = "";
			this->_x_region = "";
			this->_x_city = "";
			this->_x_street = "";
			this->_x_house = "";
			this->_x_recipient = "";
			this->_x_contact_name = "";
		}

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
	//	key
		int recipient_key( ) const
		{ return this->_i_recipient; }

		void recipient_key( const int &i_recipient )
		{ this->_i_recipient = i_recipient; }

	//-------------------------------------------------------------------------
	//	zipcode
		const QString& zipcode( ) const
		{ return this->_x_zipcode; }

		void zipcode( const QString &x_zipcode )
		{ this->_x_zipcode = x_zipcode; }

	//-------------------------------------------------------------------------
	//	state
		const QString& state( ) const
		{ return this->_x_state; }

		void state( const QString &x_state )
		{ this->_x_state = x_state; }

	//-------------------------------------------------------------------------
	//	region
		const QString& region( ) const
		{ return this->_x_region; }

		void region( const QString &x_region )
		{ this->_x_region = x_region; }

	//-------------------------------------------------------------------------
	//	city
		const QString& city( ) const
		{ return this->_x_city; }

		void city( const QString &x_city )
		{ this->_x_city = x_city; }

	//-------------------------------------------------------------------------
	//	street
		const QString& street( ) const
		{ return this->_x_street; }

		void street( const QString &x_street )
		{ this->_x_street = x_street; }

	//-------------------------------------------------------------------------
	//	house
		const QString& house( ) const
		{ return this->_x_house; }

		void house( const QString &x_house )
		{ this->_x_house = x_house; }

	//-------------------------------------------------------------------------
	//	recipient
		const QString& recipient( ) const
		{ return this->_x_recipient; }

		void recipient( const QString &x_recipient )
		{ this->_x_recipient = x_recipient; }

	//-------------------------------------------------------------------------
	//	contact_name
		const QString& contact_name( ) const
		{ return this->_x_contact_name; }

		void contact_name( const QString &x_contact_name )
		{ this->_x_contact_name = x_contact_name; }

	//-------------------------------------------------------------------------
	//	full_recipient
		QString full_recipient( ) const
		{
			return QString(
							this->_x_recipient +
							(
								this->_x_contact_name.length( )
								? "\n" + this->_x_contact_name
								: ""
							)
						  );
		}
	//-------------------------------------------------------------------------
	//	full_address
		QString full_address( ) const
		{
			return QString(
							this->_x_state +
							(
								this->_x_region.length( )
								? ", " + this->_x_region
								: ""
							) +
							(
								this->_x_city.length( )
								? ",\n" + this->_x_city
								: "\n"
							) +
							(
								this->_x_street.length( )
								? ", " + this->_x_street
								: ""
							) +
							(
								this->_x_house.length( )
								? ", " + this->_x_house
								: ""
							)
						 );
		}


	//=========================================================================
	//		OPERATORS
	//=========================================================================
	public:
		data_recipient& operator=( const data_recipient &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
			this->_i_recipient = rhs._i_recipient;
			this->_x_zipcode = rhs._x_zipcode;
			this->_x_state = rhs._x_state;
			this->_x_region = rhs._x_region;
			this->_x_city = rhs._x_city;
			this->_x_street = rhs._x_street;
			this->_x_house = rhs._x_house;
			this->_x_recipient = rhs._x_recipient;
			this->_x_contact_name = rhs._x_contact_name;

			return *this;
		}

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		int			_i_recipient;
		QString	_x_zipcode;
		QString	_x_state;
		QString	_x_region;
		QString	_x_city;
		QString	_x_street;
		QString	_x_house;
		QString	_x_recipient;
		QString	_x_contact_name;

	};//class data_recipient
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			data_recipient_collection
//#############################################################################
	class data_recipient_collection
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	//-------------------------------------------------------------------------
		data_recipient_collection( const data_recipient_collection &rhs );
	public:
	//-------------------------------------------------------------------------
		data_recipient_collection( ) :
			_data( 0 )
		{ }
	//-------------------------------------------------------------------------
		virtual ~data_recipient_collection( )
		{ this->free( ); }

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

	//-------------------------------------------------------------------------
		void free_data_pointer( )
		{
			if( !this->_data )
			{
				return;
			}
			//free pointer to list
			//but save pointers on list elements
			delete _data;
			this->_data = 0;
		}

	//-------------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
				data_recipient *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	//-------------------------------------------------------------------------
		void append( data_recipient *r )
		{
			if( !this->_data )
			{
				this->_data = new QList<data_recipient *>;
			}
			this->_data->append( r );
		}

	//-------------------------------------------------------------------------
		QList<data_recipient *>* list( )
		{ return this->_data; }

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
		data_recipient_collection& operator=(
										const data_recipient_collection &rhs
											);
	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		QList<data_recipient *>	*_data;

	};//class data_recipient_collection
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			class data_adapter_recipient
//#############################################################################
	class data_adapter_recipient
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_adapter_recipient( const data_adapter_recipient &rhs );

	public:
	//-------------------------------------------------------------------------
		explicit data_adapter_recipient( espira::qt_dbms *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	//-------------------------------------------------------------------------
		~data_adapter_recipient( );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		void check_dbms( ) const;
	//-------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	//-------------------------------------------------------------------------
		QString make_filter( const data_recipient &r_filter ) const;
	//-------------------------------------------------------------------------
		void make_params(
						const data_recipient &r,
						QVector<QVariant> &params,
						QVector<QString> &param_names
						) const;
	//-------------------------------------------------------------------------
		void execute( const QString &s_sql, const data_recipient &r ) const;
	//-------------------------------------------------------------------------
		void string_list( const QString &s_qry, QStringList &lst ) const;

	public:
	//-------------------------------------------------------------------------
		int newkey( ) const;
	//-------------------------------------------------------------------------
		data_recipient_collection*
								select( const data_recipient &r_filter ) const;
	//-------------------------------------------------------------------------
		void insert( const data_recipient &recipient ) const;
	//-------------------------------------------------------------------------
		void update( const data_recipient &recipient ) const;
	//-------------------------------------------------------------------------
		void del( const data_recipient &recipient ) const;
	//-------------------------------------------------------------------------
		void states( QStringList &lst ) const;
	//-------------------------------------------------------------------------
		void regions( QStringList &lst ) const;

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	private:

	public:

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
		data_adapter_recipient& operator=( const data_adapter_recipient &rhs );

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;
		static const QString _s_sql_states;
		static const QString _s_sql_regions;

		espira::qt_dbms *_dbms;

	};//class data_adapter_recipient
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace envelope_printing

#endif // __DATA_ADAPTER_RECIPIENT_H__
