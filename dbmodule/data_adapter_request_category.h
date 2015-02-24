//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 25-09-2013
//		Date update	: 01-10-2013
//		Comment		:
//=============================================================================
#ifndef __DATA_ADAPTER_REQUEST_CATEGORY_H__
#define __DATA_ADAPTER_REQUEST_CATEGORY_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace mac_mediator
{

//#############################################################################
//			class data_request_category
//#############################################################################
    class data_request_category
	{
        enum field_data_request_category
        {
            num_field_request_category_id = 0,
            num_field_request_category_title = 1,
            fields_count = 2
        };
    //=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
        data_request_category( ) :
            _i_request_category(0),
            _x_request_category("")
        { }

	//-------------------------------------------------------------------------
		explicit
        data_request_category( const data_request_category &rhs ) :
            _i_request_category(rhs._i_request_category),
            _x_request_category(rhs._x_request_category)
        { }

	//-------------------------------------------------------------------------
		explicit
        data_request_category( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_request_category = row[num_field_request_category_id].toInt( );
            this->_x_request_category = row[num_field_request_category_title].toString( );
        }

	//-------------------------------------------------------------------------
		explicit
        data_request_category( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_request_category = (*p_row)[num_field_request_category_id].toInt( );
            this->_x_request_category = (*p_row)[num_field_request_category_title].toString( );
		}
	//-------------------------------------------------------------------------
        ~data_request_category( )
		{
            qDebug( ) << "deleted : " << this->_i_request_category;
		}

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_request_category = 0;
            this->_x_request_category.clear();
        }

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
    //	request_category_id
        int request_category_id( ) const
        { return this->_i_request_category; }

        void request_category_id( const int &i_request_category )
        { this->_i_request_category = i_request_category; }

	//-------------------------------------------------------------------------
    //	request_category
        const QString& request_category( ) const
        { return this->_x_request_category; }

        void request_category( const QString &x_request_category )
        { this->_x_request_category = x_request_category; }

    //=========================================================================
	//		OPERATORS
	//=========================================================================
	public:
        data_request_category& operator=( const data_request_category &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_i_request_category = rhs._i_request_category;
            this->_x_request_category = rhs._x_request_category;

			return *this;
		}

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
        int     _i_request_category;        //--id категории обращения
        QString _x_request_category;        //--название категории обращения

    };//class data_request_category
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			data_request_category_collection
//#############################################################################
    class data_request_category_collection
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	//-------------------------------------------------------------------------
        data_request_category_collection( const data_request_category_collection &rhs );
	public:
	//-------------------------------------------------------------------------
        data_request_category_collection( ) :
			_data( 0 )
		{ }
	//-------------------------------------------------------------------------
        virtual ~data_request_category_collection( )
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
                data_request_category *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	//-------------------------------------------------------------------------
        void append( data_request_category *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_request_category *>;
			}
			this->_data->append( r );
		}

	//-------------------------------------------------------------------------
        QList<data_request_category *>* list( )
		{ return this->_data; }

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
        data_request_category_collection& operator=(
                                        const data_request_category_collection &rhs
											);
	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
        QList<data_request_category *>	*_data;

    };//class data_request_category_collection
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			class data_adapter_request_category
//#############################################################################
	class data_adapter_request_category
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_adapter_request_category( const data_adapter_request_category &rhs );

	public:
	//-------------------------------------------------------------------------
		explicit data_adapter_request_category( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	//-------------------------------------------------------------------------
		~data_adapter_request_category( );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		void check_dbms( ) const;
	//-------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	//-------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_request_category &r ) const;

	public:
	//-------------------------------------------------------------------------
		int newkey( ) const;
	//-------------------------------------------------------------------------
        data_request_category_collection* select( ) const;
	//-------------------------------------------------------------------------
        void insert( const data_request_category &mr ) const;
	//-------------------------------------------------------------------------
        void update( const data_request_category &mr ) const;
	//-------------------------------------------------------------------------
        void del( const data_request_category &mr ) const;

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	private:

	public:

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
		data_adapter_request_category& operator=( const data_adapter_request_category &rhs );

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_request_category

//#############################################################################
//-----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_REQUEST_CATEGORY_H__
