//$Header
//==============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 11-11-2010
//		Date update	: 20-06-2013
//		Comment		: Implementation of qt_data_row class.
//==============================================================================
#include <QDebug>

#include <stdexcept>

#include "qt_data_row.h"

namespace espira
{

namespace db
{

//#############################################################################
//			class qt_data_row
//#############################################################################
//=============================================================================
//		CONSTRUCTION/DESTRUCTION
//=============================================================================
	///------------------------------------------------------------------------
	///	qt_data_row::~qt_data_row( )
	///
	qt_data_row::~qt_data_row( )
	{
		if( this->_data )
		{
			this->free( );
		}
		qDebug( ) << "the qt_data_row object destroyed correctly";
	}

//=============================================================================
//		OPERATIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	operator[]( int i_column )
	///
	QVariant& qt_data_row::operator[]( int i_column )
	{
		if( !this->_data )
		{
			throw std::runtime_error( "qt_data_row not initialized" );
		}
		if( i_column < 0 || i_column >= this->_data->size( ) )
		{
			throw std::out_of_range( "index of value qt_data_row out of range" );
		}
		return *( this->_data->operator[]( i_column ) );
	}
	///------------------------------------------------------------------------
	///	friend
	///	QDebug operator<<( QDebug q_debug, const qt_data_row &row )
	///
	QDebug operator<<( QDebug q_debug, const qt_data_row &row )
	{
		if( !row._data )
		{
			return q_debug;
		}
		QDebug dbg = q_debug.nospace( );

		qt_data_row::data_vector::const_iterator iter = row._data->begin( );
		for( ; iter != row._data->end( ); ++iter )
		{
			dbg << *(*iter) << "\t|";
		}

		return q_debug.space( );
	}


//=============================================================================
//		FUNCTIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	free( )
	///
	void qt_data_row::free( )
	{
		if( !this->_data )
		{
			return;
		}
		while( this->_data->size( ) )
		{
			//get last element
			QVariant *value = this->_data->last( );
			//remove last element from vector
			this->_data->pop_back( );
			//delete last element
			delete value;
		}
		delete _data;

		this->_data = 0;
	}

	///------------------------------------------------------------------------
	///	append( const QVariant &value )
	///
	void qt_data_row::append( const QVariant &value )
	{
		if( !this->_data )
		{
			this->_data =  new data_vector;
		}
		this->_data->append( new QVariant( value ) );
	}

    ///------------------------------------------------------------------------
    ///	append( QVariant *pval )
    ///
    void qt_data_row::append( QVariant *pval )
    {
        if( !this->_data )
        {
            this->_data =  new data_vector;
        }
        this->_data->append( pval );
    }

    ///------------------------------------------------------------------------
	///	append( const QVector<QVariant> &vector )
	///
	void qt_data_row::append( const QVector<QVariant> &vector )
	{
		if( !this->_data )
		{
			this->_data =  new data_vector;
		}
		this->_data->reserve( vector.size( ) );
		QVector<QVariant>::const_iterator iter = vector.begin( );
		for( ; iter != vector.end( ); ++iter )
		{
			this->_data->append( new QVariant( *iter ) );
		}
	}

//class qt_data_row
//#############################################################################
//-----------------------------------------------------------------------------

//#############################################################################
//			class qt_data_row_collection
//#############################################################################
//=============================================================================
//		OPERATIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	operator[]( int i_row )
	///
	qt_data_row* qt_data_row_collection::operator[]( int i_row )
	{
		if( !this->_data )
		{
			throw std::runtime_error(
								"qt_data_row_collection not initialized"
									);
		}
		if( i_row < 0 || i_row >= this->_data->size( ) )
		{
			throw std::out_of_range(
							"index of row qt_data_row_collection "
							"out of range"
								   );
		}
		return this->_data->operator[]( i_row );
	}

	///------------------------------------------------------------------------
	///	operator<<( QDebug q_debug, const qt_data_row_collection &rows )
	///
	QDebug operator<<( QDebug q_debug, const qt_data_row_collection &rows )
	{
		if( !rows._data )
		{
			return q_debug;
		}

		qt_data_row_collection::rows_vector::const_iterator iter =
														rows._data->begin( );
		for( ; iter != rows._data->end( ); ++iter )
		{
			q_debug << *(*iter);
		}

		return q_debug;
	}

//=============================================================================
//		FUNCTIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	free( )
	///
	void qt_data_row_collection::free( )
	{
		if( !this->_data )
		{
			return;
		}
		while( this->_data->size( ) )
		{
			//get last element
			qt_data_row *row = this->_data->last( );
			//remove last element from vector
			this->_data->pop_back( );
			//delete last element
			delete row;
		}
		delete _data;

		this->_data = 0;
	}

	///------------------------------------------------------------------------
	///	append( const qt_data_row *row )
	///
	void qt_data_row_collection::append( qt_data_row *row )
	{
		if( !this->_data )
		{
			this->_data =  new rows_vector;
		}
		this->_data->append( row );
	}

//class qt_data_row_collection
//#############################################################################
//-----------------------------------------------------------------------------
}//namespace db

}//namespace espira
