/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 25-06-2013
///		Date update	: 25-10-2013
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_SO_H__
#define __DATA_ADAPTER_SO_H__

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
///			class data_so
/// ############################################################################
    class data_so
	{
    private:
        enum data_so_field
        {
            field_i_so = 0,
            field_so_title = 1,
            field_so_address = 2,
            field_so_phones = 3,
            num_of_fields = 4
        };

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_so( ) :
            _i_so( 0 ),
            _x_so_title( "" ),
            _x_so_address( "" ),
            _x_so_phones( "" )
		{ }

	/// ------------------------------------------------------------------------
		explicit
        data_so( const data_so &rhs ) :
            _i_so( rhs._i_so ),
            _x_so_title( rhs._x_so_title ),
            _x_so_address( rhs._x_so_address ),
            _x_so_phones( rhs._x_so_phones )
		{ }

	/// ------------------------------------------------------------------------
		explicit
        data_so( const QVector<QVariant> &row )
		{
            if( row.size( ) < num_of_fields )
            {
                this->clear_data( );
            }
            this->_i_so = row[field_i_so].toInt( );
            if( row[field_so_title].isValid( ) )
            {
                this->_x_so_title = row[field_so_title].toString( );
            }
            if( row[field_so_address].isValid( ) )
            {
                this->_x_so_address = row[field_so_address].toString( );
            }
            if( row[field_so_phones].isValid( ) )
            {
                this->_x_so_phones = row[field_so_phones].toString( );
            }
        }

	/// ------------------------------------------------------------------------
		explicit
        data_so( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < num_of_fields )
            {
                this->clear_data( );
            }
            this->_i_so = (*p_row)[field_i_so].toInt( );
            if( (*p_row)[field_so_title].isValid( ) )
            {
                this->_x_so_title = (*p_row)[field_so_title].toString( );
            }
            if( (*p_row)[field_so_address].isValid( ) )
            {
                this->_x_so_address = (*p_row)[field_so_address].toString( );
            }
            if( (*p_row)[field_so_phones].isValid( ) )
            {
                this->_x_so_phones = (*p_row)[field_so_phones].toString( );
            }

            qDebug() << "created:" << _x_so_title;
        }

	/// ------------------------------------------------------------------------
        ~data_so( )
		{
			qDebug( ) << "deleted : " << this->_x_so_title;
		}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_so = 0;
            this->_x_so_title.clear( );
            this->_x_so_address.clear( );
            this->_x_so_phones.clear( );
		}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
	///	key
        int so_key( ) const
        { return this->_i_so; }

        void so_key( const int &i_so )
        { this->_i_so = i_so; }

	/// ------------------------------------------------------------------------
	///	title
		const QString& title( ) const
		{ return this->_x_so_title; }

		void title( const QString &x_so_title )
		{ this->_x_so_title = x_so_title; }

    /// ------------------------------------------------------------------------
    ///	address
        const QString& address( ) const
        { return this->_x_so_address; }

        void address( const QString &x_so_address )
        { this->_x_so_address = x_so_address; }

    /// ------------------------------------------------------------------------
    ///	phones
        const QString& phones( ) const
        { return this->_x_so_phones; }

        void phones( const QString &x_so_phones )
        { this->_x_so_phones = x_so_phones; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	public:
        data_so& operator=( const data_so &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            _i_so = rhs._i_so;
            _x_so_title = rhs._x_so_title;
            _x_so_address = rhs._x_so_address;
            _x_so_phones = rhs._x_so_phones;

			return *this;
		}

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        int     _i_so;
        QString _x_so_title;
        QString _x_so_address;
        QString _x_so_phones;

    };//class data_so
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
//			data_so_collection
/// ############################################################################
    class data_so_collection
	{
	/// ========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
        data_so_collection( const data_so_collection &rhs );
	public:
	/// ------------------------------------------------------------------------
        data_so_collection( ) :
			_data( 0 )
		{ }
	/// ------------------------------------------------------------------------
        virtual ~data_so_collection( )
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
                data_so *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	/// ------------------------------------------------------------------------
        void append( data_so *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_so *>;
			}
			this->_data->append( r );
		}

	/// ------------------------------------------------------------------------
        QList<data_so *>* list( )
		{ return this->_data; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_so_collection& operator=(
                                        const data_so_collection &rhs
											);
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        QList<data_so *>	*_data;

    };//class data_so_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_so
/// ############################################################################
    class data_adapter_so
	{
    private:
        enum data_adapter_so_constant
        {
            minimum_syms_for_search = 2
        };

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        data_adapter_so( const data_adapter_so &rhs );

	public:
	/// ------------------------------------------------------------------------
        explicit data_adapter_so( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	/// ------------------------------------------------------------------------
        ~data_adapter_so( );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	/// ------------------------------------------------------------------------
        QString make_filter( const long long &i_TIB_code ) const;
	/// ------------------------------------------------------------------------
		void make_params(
                        const data_so &r,
						QVector<QVariant> &params,
						QVector<QString> &param_names
						) const;
	/// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_so &r ) const;
	/// ------------------------------------------------------------------------
		void string_list( const QString &s_qry, QStringList &lst ) const;

	public:
	/// ------------------------------------------------------------------------
		int newkey( ) const;
	/// ------------------------------------------------------------------------
        data_so_collection*
                                select( const QString &s_filter ) const;
    /// ------------------------------------------------------------------------
        data_so* select( const long long &i_TIB_code ) const;
	/// ------------------------------------------------------------------------
        void insert( const data_so &address ) const;
	/// ------------------------------------------------------------------------
        void update( const data_so &address ) const;
	/// ------------------------------------------------------------------------
        void del( const data_so &address ) const;

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	private:

	public:

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_adapter_so& operator=( const data_adapter_so &rhs );

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

    };//class data_adapter_so
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_SO_H__
