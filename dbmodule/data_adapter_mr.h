//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 22-09-2013
//		Date update	: 25-09-2013
//		Comment		:
//=============================================================================
#ifndef __DATA_ADAPTER_MR_H__
#define __DATA_ADAPTER_MR_H__

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
//			class data_ad
//#############################################################################
    class data_mr
	{
        enum field_data_mr
        {
            num_field_mr_id = 0,
            num_field_cc_id = 1,
            num_field_ad_id = 2,
            num_field_mr_title = 3,
            fields_count = 4
        };
    //=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
        data_mr( ) :
            _i_mr(0),
            _i_class_code_mr(0),
            _i_ad(0),
            _x_mr("")
        { }

	//-------------------------------------------------------------------------
		explicit
        data_mr( const data_mr &rhs ) :
            _i_mr(rhs._i_mr),
            _i_class_code_mr(rhs._i_class_code_mr),
            _i_ad(rhs._i_ad),
            _x_mr(rhs._x_mr)
        { }

	//-------------------------------------------------------------------------
		explicit
        data_mr( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_mr = row[num_field_mr_id].toInt( );
            this->_i_class_code_mr = row[num_field_cc_id].toInt( );
            this->_i_ad = row[num_field_ad_id].toInt( );
            this->_x_mr = row[num_field_mr_title].toString( );
        }

	//-------------------------------------------------------------------------
		explicit
        data_mr( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_i_mr = (*p_row)[num_field_mr_id].toInt( );
            this->_i_class_code_mr = (*p_row)[num_field_cc_id].toInt( );
            this->_i_ad = (*p_row)[num_field_ad_id].toInt( );
            this->_x_mr = (*p_row)[num_field_mr_title].toString( );
		}
	//-------------------------------------------------------------------------
        ~data_mr( )
		{
            qDebug( ) << "deleted : " << this->_i_mr << " " +
                         this->_x_mr + '\0';
		}

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		void clear_data( )
		{
            this->_i_mr = 0;
            this->_i_class_code_mr = 0;
            this->_i_ad = 0;
            this->_x_mr.clear( );
        }

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
    //	mr_id
        int mr_id( ) const
        { return this->_i_mr; }

        void mr_id( const int &i_mr )
        { this->_i_mr = i_mr; }

	//-------------------------------------------------------------------------
    //	class_code_id
        int class_code_id( ) const
        { return this->_i_class_code_mr; }

        void class_code_id( const int &i_class_code_mr )
        { this->_i_class_code_mr = i_class_code_mr; }

	//-------------------------------------------------------------------------
    //	ad_id
        int ad_id( ) const
        { return this->_i_ad; }

        void ad_id( const int &i_ad )
        { this->_i_ad = i_ad; }

	//-------------------------------------------------------------------------
    //	mr_title
        const QString& mr_title( ) const
        { return this->_x_mr; }

        void mr_title( const QString &x_mr )
        { this->_x_mr = x_mr; }

    //=========================================================================
	//		OPERATORS
	//=========================================================================
	public:
        data_mr& operator=( const data_mr &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_i_mr = rhs._i_mr;
            this->_i_class_code_mr = rhs._i_class_code_mr;
            this->_i_ad = rhs._i_ad;
            this->_x_mr = rhs._x_mr;

			return *this;
		}

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
        int     _i_mr;              //--id района
        int     _i_class_code_mr;   //--id кода классификатора
        int     _i_ad;              //--id округа
        QString _x_mr;              //--муниципальный район

    };//class data_mr
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			data_mr_collection
//#############################################################################
    class data_mr_collection
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	//-------------------------------------------------------------------------
        data_mr_collection( const data_mr_collection &rhs );
	public:
	//-------------------------------------------------------------------------
        data_mr_collection( ) :
			_data( 0 )
		{ }
	//-------------------------------------------------------------------------
        virtual ~data_mr_collection( )
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
                data_mr *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	//-------------------------------------------------------------------------
        void append( data_mr *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_mr *>;
			}
			this->_data->append( r );
		}

	//-------------------------------------------------------------------------
        QList<data_mr *>* list( )
		{ return this->_data; }

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
        data_mr_collection& operator=(
                                        const data_mr_collection &rhs
											);
	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
        QList<data_mr *>	*_data;

    };//class data_mr_collection
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			class data_adapter_mr
//#############################################################################
	class data_adapter_mr
	{
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_adapter_mr( const data_adapter_mr &rhs );

	public:
	//-------------------------------------------------------------------------
		explicit data_adapter_mr( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	//-------------------------------------------------------------------------
		~data_adapter_mr( );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		void check_dbms( ) const;
	//-------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	//-------------------------------------------------------------------------
        QString make_filter( const data_mr &r_filter ) const;
	//-------------------------------------------------------------------------
		void make_params(
                        const data_mr &r,
						QVector<QVariant> &params,
						QVector<QString> &param_names
						) const;
	//-------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_mr &r ) const;

	public:
	//-------------------------------------------------------------------------
		int newkey( ) const;
	//-------------------------------------------------------------------------
        data_mr_collection*
                                select( const data_mr &r_filter ) const;
	//-------------------------------------------------------------------------
        void insert( const data_mr &mr ) const;
	//-------------------------------------------------------------------------
        void update( const data_mr &mr ) const;
	//-------------------------------------------------------------------------
        void del( const data_mr &mr ) const;

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	private:

	public:

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
		data_adapter_mr& operator=( const data_adapter_mr &rhs );

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

	};//class data_adapter_mr

//#############################################################################
//-----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_MR_H__
