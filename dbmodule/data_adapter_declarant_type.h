///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 30-01-2014
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_DECLARANT_TYPE_H__
#define __DATA_ADAPTER_DECLARANT_TYPE_H__

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

/// ############################################################################
///			class data_declarant_type
/// ############################################################################
    class data_declarant_type
	{
    public:
        enum field_data_declarant_type
        {
            num_field_id = 0,
            num_field_title = 1,
            fields_count = 2
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_declarant_type( ) :
            _i_declarant_type(0),
            _x_declarant_type("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_declarant_type( const data_declarant_type &rhs ) :
            _i_declarant_type(rhs._i_declarant_type),
            _x_declarant_type(rhs._x_declarant_type)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_declarant_type( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_declarant_type = row[num_field_id].toInt( );
            this->_x_declarant_type = row[num_field_title].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_declarant_type( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_declarant_type = (*p_row)[num_field_id].toInt( );
            this->_x_declarant_type = (*p_row)[num_field_title].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_declarant_type( )
		{
            qDebug( ) << "deleted : " << this->_i_declarant_type << " " +
                                         this->_x_declarant_type;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_declarant_type = 0;
            this->_x_declarant_type.clear();
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_declarant_type
        int id_declarant_type( ) const
        { return this->_i_declarant_type; }

        void id_declarant_type( const int &id )
        { this->_i_declarant_type = id; }

    /// ------------------------------------------------------------------------
    ///	declarant_type_title
        const QString& declarant_type_title( ) const
        { return this->_x_declarant_type; }

        void declarant_type_title( const QString &x_title )
        { this->_x_declarant_type = x_title; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_declarant_type& operator=( const data_declarant_type &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_i_declarant_type = rhs._i_declarant_type;
            this->_x_declarant_type = rhs._x_declarant_type;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _i_declarant_type;  //--id типа заявителя
        QString _x_declarant_type;  //--тип заявителя

    };//class data_declarant_type
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_declarant_type_collection
/// ############################################################################
    class data_declarant_type_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_declarant_type_collection( const data_declarant_type_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_declarant_type_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_declarant_type_collection( )
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
                data_declarant_type *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_declarant_type *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_declarant_type *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_declarant_type *>* list( )
		{ return this->_data; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_declarant_type_collection& operator=(
                                        const data_declarant_type_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_declarant_type *>	*_data;

    };//class data_declarant_type_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_declarant_type
/// ############################################################################
    class data_adapter_declarant_type
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_declarant_type( const data_adapter_declarant_type &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_declarant_type( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_declarant_type( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
        /// ------------------------------------------------------------------------
        void bind_parameters_insert(
                                    espira::db::qt_sqlite_command *pcmd,
                                    int id_new,
                                    const data_declarant_type &dt
                                   ) const;
        /// ------------------------------------------------------------------------
        void bind_parameters_update(
                                    espira::db::qt_sqlite_command *pcmd,
                                    const data_declarant_type &dt
                                   ) const;

	public:
    /// ------------------------------------------------------------------------
		int newkey( ) const;
    /// ------------------------------------------------------------------------
        data_declarant_type_collection* select( ) const;
    /// ------------------------------------------------------------------------
        void insert(data_declarant_type &ad ) const;
    /// ------------------------------------------------------------------------
        void update( const data_declarant_type &ad ) const;
    /// ------------------------------------------------------------------------
        void del( const data_declarant_type &ad ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_declarant_type& operator=( const data_adapter_declarant_type &rhs );

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

    };//class data_adapter_declarant_type

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_DECLARANT_TYPE_H__
