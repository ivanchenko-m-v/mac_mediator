///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 27-09-2013
///		Date update	: 16-01-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_MEDIATOR_H__
#define __DATA_ADAPTER_MEDIATOR_H__

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
///			class data_mediator
/// ############################################################################
    class data_mediator
	{
        enum field_data_mediator
        {
            num_field_mediator_id = 0,
            num_field_mediator = 1,
            num_field_mediator_phone = 2,
            num_field_note = 3,
            fields_count = 4
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_mediator( ) :
            _i_mediator(0),
            _x_mediator(""),
            _x_mediator_phone(""),
            _x_note(""),
            _x_permissions("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_mediator( const data_mediator &rhs ) :
            _i_mediator( rhs._i_mediator ),
            _x_mediator(rhs._x_mediator),
            _x_mediator_phone(rhs._x_mediator_phone),
            _x_note(rhs._x_note),
            _x_permissions("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_mediator( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            _i_mediator = row[num_field_mediator_id].toInt( );
            _x_mediator = row[num_field_mediator].toString( );
            _x_mediator_phone = row[num_field_mediator_phone].toString( );
            _x_note = row[num_field_note].toString( );
            _x_permissions.clear( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_mediator( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            _i_mediator = (*p_row)[num_field_mediator_id].toInt( );
            _x_mediator = (*p_row)[num_field_mediator].toString( );
            _x_mediator_phone = (*p_row)[num_field_mediator_phone].toString( );
            _x_note = (*p_row)[num_field_note].toString( );
            _x_permissions.clear( );
		}
    /// ------------------------------------------------------------------------
        ~data_mediator( )
		{
            qDebug( ) << "deleted : " << this->_i_mediator << " " +
                                         this->_x_mediator;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            _i_mediator = 0;
            _x_mediator.clear( );
            _x_mediator_phone.clear( );
            _x_note.clear( );
            _x_permissions.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	mediator_id
        int mediator_id( ) const
        { return this->_i_mediator; }

        void mediator_id( const int &i_mediator )
        { this->_i_mediator = i_mediator; }

    /// ------------------------------------------------------------------------
    ///	mediator
        const QString& mediator( ) const
        { return this->_x_mediator; }

        void mediator( const QString &x_mediator )
        { this->_x_mediator = x_mediator; }

    /// ------------------------------------------------------------------------
    ///	mediator_phone
        const QString& mediator_phone( ) const
        { return this->_x_mediator_phone; }

        void mediator_phone( const QString &x_mediator_phone )
        { this->_x_mediator_phone = x_mediator_phone; }

    /// ------------------------------------------------------------------------
    ///	note
        const QString& note( ) const
        { return this->_x_note; }

        void note( const QString &x_note )
        { this->_x_note = x_note; }

    /// ------------------------------------------------------------------------
    ///	permissions
        const QString& permissions( ) const
        { return this->_x_permissions; }

        void permissions( const QString &x_permissions )
        { this->_x_permissions = x_permissions; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_mediator& operator=( const data_mediator &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            _i_mediator = rhs._i_mediator;
            _x_mediator = rhs._x_mediator;
            _x_mediator_phone = rhs._x_mediator_phone;
            _x_note = rhs._x_note;
            _x_permissions = rhs._x_permissions;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _i_mediator;       //--id медиатора
        QString _x_mediator;       //--ФИО медиатора
        QString _x_mediator_phone; //--телефон медиатора
        QString _x_note;           //--примечание

        QString _x_permissions;    //--права
    };//class data_mediator
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_mediator_collection
/// ############################################################################
    class data_mediator_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_mediator_collection( const data_mediator_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_mediator_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_mediator_collection( )
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
                data_mediator *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_mediator *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_mediator *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_mediator *>* list( )
		{ return this->_data; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_mediator_collection& operator=(
                                        const data_mediator_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_mediator *>	*_data;

    };//class data_mediator_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_mediator
/// ############################################################################
	class data_adapter_mediator
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		data_adapter_mediator( const data_adapter_mediator &rhs );

	public:
    /// ------------------------------------------------------------------------
		explicit data_adapter_mediator( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
		~data_adapter_mediator( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void check_dbms( ) const;
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void cmd_params_select_authorized(
                          espira::db::qt_sqlite_command *pcmd,
                          const QString &x_login, const QString &x_hash
                                         ) const;
    /// ------------------------------------------------------------------------
        void cmd_params_select_permissions(
                          espira::db::qt_sqlite_command *pcmd,
                          int id_mediator
                                          ) const;
    /// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_mediator &r ) const;

	public:
    /// ------------------------------------------------------------------------
		int newkey( ) const;
    /// ------------------------------------------------------------------------
        data_mediator_collection*
                                select( ) const;
    /// ------------------------------------------------------------------------
        data_mediator_collection*
                                select( int id_authorized_mediator ) const;
    /// ------------------------------------------------------------------------
        QString select_permissions( int id_mediator ) const;
    /// ------------------------------------------------------------------------
        data_mediator* select_authorized(
                                            const QString &x_login,
                                            const QString &x_hash
                                        ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_mediator &mediator ) const;
    /// ------------------------------------------------------------------------
        void update( const data_mediator &mediator ) const;
    /// ------------------------------------------------------------------------
        void del( const data_mediator &mediator ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
		data_adapter_mediator& operator=( const data_adapter_mediator &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;
        static const QString _s_sql_select_one;
        static const QString _s_sql_select_authirized;
        static const QString _s_sql_select_permissions;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_mediator

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_MEDIATOR_H__
