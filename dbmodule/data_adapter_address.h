/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 25-06-2013
///		Date update	: 23-10-2013
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_ADDRESS_H__
#define __DATA_ADAPTER_ADDRESS_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace mac_mediator
{

/// ############################################################################
///			class data_address
/// ############################################################################
    class data_address
	{
    private:
        enum data_address_field
        {
            field_TIB_code = 0,
            field_extra_code = 1,
            field_street_code = 2,
            field_municipal_district = 3,
            field_address = 4,
            num_of_fields = 5
        };

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_address( ) :
            _i_TIB_code( 0 ),
            _i_extra_code( 0 ),
            _i_street_code( 0 ),
            _i_municipal_district( 0 ),
            _x_address( "" )
		{ }

	/// ------------------------------------------------------------------------
		explicit
        data_address( const data_address &rhs ) :
            _i_TIB_code( rhs._i_TIB_code ),
            _i_extra_code( rhs._i_extra_code ),
            _i_street_code( rhs._i_street_code ),
            _i_municipal_district( rhs._i_municipal_district ),
            _x_address( rhs._x_address )
		{ }

	/// ------------------------------------------------------------------------
		explicit
        data_address( const QVector<QVariant> &row )
		{
            if( row.size( ) < num_of_fields )
            {
                this->clear_data( );
            }
            _i_TIB_code = row[field_TIB_code].toLongLong( );
            _i_extra_code = row[field_extra_code].toInt( );
            _i_street_code = row[field_street_code].toInt( );
            _i_municipal_district = row[field_municipal_district].toInt( );
            _x_address = row[field_address].toString( );
        }

	/// ------------------------------------------------------------------------
		explicit
        data_address( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < num_of_fields )
            {
                this->clear_data( );
            }
            _i_TIB_code = (*p_row)[field_TIB_code].toLongLong( );
            _i_extra_code = (*p_row)[field_extra_code].toInt( );
            _i_street_code = (*p_row)[field_street_code].toInt( );
            _i_municipal_district = (*p_row)[field_municipal_district].toInt( );
            _x_address = (*p_row)[field_address].toString( );
            qDebug() << "created:" << _x_address;
        }

	/// ------------------------------------------------------------------------
        ~data_address( )
		{
			qDebug( ) << "deleted : " << QString::number( this->_i_TIB_code ) + " " +
										 QString::number( this->_i_extra_code ) + " " +
										 this->_x_address;
		}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_TIB_code = 0;
            this->_i_extra_code = 0;
            this->_i_street_code = 0;
            this->_i_municipal_district = 0;
            this->_x_address = "";
		}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
	///	key
        int address_key( ) const
        { return this->_i_TIB_code; }

        void address_key( const int &i_address )
        { this->_i_TIB_code = i_address; }

	/// ------------------------------------------------------------------------
	///	extra_code
		short extra_code( ) const
		{ return this->_i_extra_code; }

		void extra_code( const short &i_extra_code )
		{ this->_i_extra_code = i_extra_code; }

    /// ------------------------------------------------------------------------
    ///	street code
        long long street_code( ) const
        { return this->_i_street_code; }

        void street_code( const int &i_street_code )
        { this->_i_street_code = i_street_code; }

    /// ------------------------------------------------------------------------
    ///	municipal district
        int municipal_district( ) const
        { return this->_i_municipal_district; }

        void municipal_district( const short &i_municipal_district )
        { this->_i_municipal_district = i_municipal_district; }

	/// ------------------------------------------------------------------------
    ///	address
        const QString& address( ) const
        { return this->_x_address; }

        void address( const QString &x_address )
        { this->_x_address = x_address; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	public:
        data_address& operator=( const data_address &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_i_TIB_code = rhs._i_TIB_code;
            this->_i_extra_code = rhs._i_extra_code;
            this->_i_street_code = rhs._i_street_code;
            this->_i_municipal_district = rhs._i_municipal_district;
            this->_x_address = rhs._x_address;

			return *this;
		}

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        long long   _i_TIB_code;
        short       _i_extra_code;
        long long   _i_street_code;
        int         _i_municipal_district;
        QString     _x_address;

    };///class data_address
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_address_collection
/// ############################################################################
    class data_address_collection
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
        data_address_collection( const data_address_collection &rhs );
	public:
	/// ------------------------------------------------------------------------
        data_address_collection( ) :
			_data( 0 )
		{ }
	/// ------------------------------------------------------------------------
        virtual ~data_address_collection( )
		{ this->free( ); }

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

	/// ------------------------------------------------------------------------
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

	/// ------------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
                data_address *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	/// ------------------------------------------------------------------------
        void append( data_address *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_address *>;
			}
			this->_data->append( r );
		}

	/// ------------------------------------------------------------------------
        QList<data_address *>* list( )
		{ return this->_data; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_address_collection& operator=(
                                        const data_address_collection &rhs
											);
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        QList<data_address *>	*_data;

    };//class data_address_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_address
/// ############################################################################
    class data_adapter_address
	{
    private:
        enum data_adapter_address_constant
        {
            minimum_syms_for_search = 3
        };

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        data_adapter_address( const data_adapter_address &rhs );

	public:
	/// ------------------------------------------------------------------------
        explicit data_adapter_address( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	/// ------------------------------------------------------------------------
        ~data_adapter_address( );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	/// ------------------------------------------------------------------------
        QString make_filter( const QString &s_filter ) const;
	/// ------------------------------------------------------------------------
		void make_params(
                        const data_address &r,
						QVector<QVariant> &params,
						QVector<QString> &param_names
						) const;
	/// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_address &r ) const;
	/// ------------------------------------------------------------------------
		void string_list( const QString &s_qry, QStringList &lst ) const;

	public:
	/// ------------------------------------------------------------------------
		int newkey( ) const;
	/// ------------------------------------------------------------------------
        data_address_collection*
                                select( const QString &s_filter ) const;
	/// ------------------------------------------------------------------------
        void insert( const data_address &address ) const;
	/// ------------------------------------------------------------------------
        void update( const data_address &address ) const;
	/// ------------------------------------------------------------------------
        void del( const data_address &address ) const;
	/// ------------------------------------------------------------------------
		void states( QStringList &lst ) const;
	/// ------------------------------------------------------------------------
		void regions( QStringList &lst ) const;

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	private:

	public:

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_adapter_address& operator=( const data_adapter_address &rhs );

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;

    };//class data_adapter_address
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_ADDRESS_H__
