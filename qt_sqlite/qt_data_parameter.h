//$Header
//==============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 11-06-2013
//		Date update	: 19-06-2013
//		Comment		: Declaration of qt_data_parameter_collection class.
//==============================================================================
#ifndef __QT_DATA_PARAMETER_H__
#define __QT_DATA_PARAMETER_H__

#include <QDebug>
#include <QVariant>
#include <QVector>

#include <stdexcept>
#include "qt_sqlite_dbvalue.h"

namespace espira
{

namespace db
{


//#############################################################################
//			class qt_data_parameter_collection
//#############################################################################
    class qt_data_parameter_collection
	{
	public:
        typedef QVector<qt_sqlite_dbvalue *>             parameter_vector;
        typedef QVector<qt_sqlite_dbvalue *>::iterator   iterator;
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
		//----------------------------------------------------------------------
        qt_data_parameter_collection( const qt_data_parameter_collection & ); //disabled

	public:
		//----------------------------------------------------------------------
        qt_data_parameter_collection( ) :
			_data( 0 )
		{ }
		//----------------------------------------------------------------------
        virtual ~qt_data_parameter_collection( )
		{
			if( this->_data )
			{
				this->free( );
			}
		}

	//==========================================================================
	//		OPERATIONS
	//==========================================================================
	private:
	//--------------------------------------------------------------------------
        const qt_data_parameter_collection&
                        operator=( const qt_data_parameter_collection & ); //disabled
	public:
	//--------------------------------------------------------------------------
        qt_sqlite_dbvalue* operator[]( int n_param );
	//--------------------------------------------------------------------------
		friend
        QDebug operator<<( QDebug q_debug, const qt_data_parameter_collection &params );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//--------------------------------------------------------------------------
		iterator begin( )
		{
			if( !this->_data )
			{
                return parameter_vector::iterator( );
			}
			return this->_data->begin( );
		}

	//--------------------------------------------------------------------------
		iterator end( )
		{
			if( !this->_data )
			{
                return parameter_vector::iterator( );
			}
			return this->_data->end( );
		}

	//--------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}
	//--------------------------------------------------------------------------
		void free( );
	//--------------------------------------------------------------------------
        void append( qt_sqlite_dbvalue *param );

	//==========================================================================
	//		FIELDS
	//==========================================================================
	private:
        parameter_vector *_data;

	};

//#############################################################################
//-----------------------------------------------------------------------------
}//namespace db

}//namespace espira

#endif // __QT_DATA_PARAMETER_H__
