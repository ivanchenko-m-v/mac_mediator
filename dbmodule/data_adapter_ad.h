///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 22-09-2013
///		Date update	: 19-12-2013
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_AD_H__
#define __DATA_ADAPTER_AD_H__

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
///			class data_ad
/// ############################################################################
    class data_ad
	{
        enum field_data_ad
        {
            num_field_ad_id = 0,
            num_field_ad_title = 1,
            num_field_ad_abbr = 2,
            fields_count = 3
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_ad( ) :
            _i_ad(0),
            _x_ad(""),
            _x_ad_abbreviation("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_ad( const data_ad &rhs ) :
            _i_ad(rhs._i_ad),
            _x_ad(rhs._x_ad),
            _x_ad_abbreviation(rhs._x_ad_abbreviation)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_ad( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_ad = row[num_field_ad_id].toInt( );
            this->_x_ad = row[num_field_ad_title].toString( );
            this->_x_ad_abbreviation = row[num_field_ad_abbr].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_ad( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_ad = (*p_row)[num_field_ad_id].toInt( );
            this->_x_ad = (*p_row)[num_field_ad_title].toString( );
            this->_x_ad_abbreviation = (*p_row)[num_field_ad_abbr].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_ad( )
		{
            qDebug( ) << "deleted : " << this->_i_ad << " " +
                                         this->_x_ad_abbreviation;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_ad = 0;
            this->_x_ad.clear();
            this->_x_ad_abbreviation.clear();
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	ad_id
        int ad_id( ) const
        { return this->_i_ad; }

        void ad_id( const int &i_ad )
        { this->_i_ad = i_ad; }

    /// ------------------------------------------------------------------------
    ///	ad_title
        const QString& ad_title( ) const
        { return this->_x_ad; }

        void ad_title( const QString &x_ad )
        { this->_x_ad = x_ad; }

    /// ------------------------------------------------------------------------
    ///	ad_abbreviation
        const QString& ad_abbreviation( ) const
        { return this->_x_ad_abbreviation; }

        void ad_abbreviation( const QString &x_ad_abbreviation )
        { this->_x_ad_abbreviation = x_ad_abbreviation; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_ad& operator=( const data_ad &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_i_ad = rhs._i_ad;
            this->_x_ad = rhs._x_ad;
            this->_x_ad_abbreviation = rhs._x_ad_abbreviation;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _i_ad;              //--название округа
        QString _x_ad;              //--заявитель
        QString _x_ad_abbreviation; //--аббревиатура округа

    };//class data_ad
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_ad_collection
/// ############################################################################
    class data_ad_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_ad_collection( const data_ad_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_ad_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_ad_collection( )
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
                data_ad *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_ad *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_ad *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_ad *>* list( )
		{ return this->_data; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_ad_collection& operator=(
                                        const data_ad_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_ad *>	*_data;

    };//class data_ad_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_ad
/// ############################################################################
	class data_adapter_ad
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		data_adapter_ad( const data_adapter_ad &rhs );

	public:
    /// ------------------------------------------------------------------------
		explicit data_adapter_ad( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
		~data_adapter_ad( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void check_dbms( ) const;
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        QString make_filter( const data_ad &r_filter ) const;
    /// ------------------------------------------------------------------------
		void make_params(
                        const data_ad &r,
						QVector<QVariant> &params,
						QVector<QString> &param_names
						) const;
    /// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_ad &r ) const;

	public:
    /// ------------------------------------------------------------------------
		int newkey( ) const;
    /// ------------------------------------------------------------------------
        data_ad_collection*
                                select( const data_ad &r_filter ) const;
    /// ------------------------------------------------------------------------
        data_ad_collection* select( ) const;
    /// ------------------------------------------------------------------------
        data_ad_collection *select(int id_authorized_mediator) const;
    /// ------------------------------------------------------------------------
        void insert( const data_ad &ad ) const;
    /// ------------------------------------------------------------------------
        void update( const data_ad &ad ) const;
    /// ------------------------------------------------------------------------
        void del( const data_ad &ad ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
		data_adapter_ad& operator=( const data_adapter_ad &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;
        static const QString _s_sql_select_for_mediator;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_ad

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_AD_H__
